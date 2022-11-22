#include<stdio.h>
#include<string.h>
#include<stdlib.h>



    struct items{
    	char item[20];
    	float price;
    	int qty;
	};    
	
	struct orders{
		char customer[50];
		char date[50];
		int numOfItems;
		struct items itm[50];
	};
	
      void generateBillHeaders(char name[50],char date[30]){
      	
      	printf("\n\n");
      	printf("\t     Ankush's Restaurant");
      	printf("\n\t -----------------------");
      	
      	printf("\nDate:%s",date);
      	printf("\nInvoice To: %s", name);
      	printf("\n");
      	printf("-----------------------------------------\n");
      	printf("Items \t\t");
      	printf("Qty \t\t");
      	printf("Total \t\t");
      	printf("\n-----------------------------------------");
      	printf("\n\n");
	  }	
	void generateBillBody(char item[30],int qty,float price){
		printf("%s\t\t",item);
		printf("%d\t\t",qty);
		printf("%.2f\t\t",qty*price);
		printf("\n");
	}
	void generateBillFooter(float total){
		
		printf("\n");
	  float dis = 0.1*total;
	  float netTotal = total-dis;
	  float cgst = 0.09*netTotal,grandTotal = netTotal + 2*cgst;
	  printf("--------------------------------------\n");
	  printf("Sub Total\t\t\t%.2f",total);
	  printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
	  printf("\n\t\t\t\t-------");
	  printf("\nNet Total\t\t\t%.2f",netTotal);
	  printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
	   printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
	   printf("\n--------------------------------------");
	   printf("\nGrand Total \t\t\t%.2f",grandTotal);
	   printf("\n--------------------------------------\n");
	  
	  
	  
	}
	

int main(){

	int n;
	
	char name[50];
	struct orders ord;
	struct orders order;
	char saveBill = 'y',contFlag = 'y';
	FILE *fp;
	int opt;
	while(contFlag == 'y'){
	//	system("clear");
		int invoiceFound = 0;
		float total = 0;
	printf("\t============Ankush's Restaurant============");
	printf("\n\nPlease select your preffered operations");
	printf("\n\n1. Generate Invoice\n");
	printf("2. Show all Invoices\n");
	printf("3. Search Invoices\n");
	printf("4. Exit\n");
	
	printf("\n\nYour choice :\t");
	scanf("%d",&opt);
	fgetc(stdin);
	
	   switch(opt){
	   	case 1:
	   	//	system("clear");
	   	printf("\nPlease entre the name of customer:\t");	
	   	fgets(ord.customer,50,stdin);
	   	ord.customer[strlen(ord.customer)-1] = 0;
	   	strcpy(ord.date,__DATE__);
	   	printf("\nPlease entre the number of items:\t");
	   	scanf("%d",&n);
	   	ord.numOfItems = n;
	   	
	   	for(int i=0;i<n;i++){
	   		fgetc(stdin);
	   		printf("\n\n");
	   		printf("Please entre the name of items %d\t",i+1);
	   		fgets(ord.itm[i].item,20,stdin);
	   		ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
	   		printf("\nPlease entre the quantity:\t");
	   		scanf("%d",&ord.itm[i].qty);
	   		printf("\nPlease entre the unit price:\t");
	   		scanf("%f",&ord.itm[i].price);
	   		total += ord.itm[i].qty * ord.itm[i].price;
		}
		
	  generateBillHeaders(ord.customer,ord.date);
	  
	  
   for(int i=0;i<ord.numOfItems;i++){
   	generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);


  }
	 generateBillFooter(total);  	
	 
	 printf("\nDo you want to save the Invoice[y/n]: ");
	 scanf("%s",&saveBill);
	 if(saveBill=='y'){
	 	fp = fopen("ResturantBill.dat","a+");
	 	fwrite(&ord,sizeof(struct orders),1,fp);
	 	if(fwrite !=0){
	 		printf("\nSuccessfully saved");
		 }
		  else{
		  	printf("\nError in saving");
		  	fclose(fp);
		  }
	 }	
		   
	   	break;
	   	
	   	case 2:
	   	//system("clear");	
	   	fp = fopen("RestaurantBill.dat","r");
	   	printf("\n ******Your Previous Invoices*****\n");
	   	
	   	while(fread(&order,sizeof(struct orders),1,fp)){
	   		float tot = 0;
		   
	  generateBillHeaders(order.customer,order.date);
	   	
	   	for(int i = 0;i<order.numOfItems;i++){
	   		
	   		generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
	   		tot+= order.itm[i].qty*order.itm[i].price;
		   }
		   
	   	generateBillFooter(total);
	    
}
fclose(fp);
	   break;
	   
	   case 3:
	   	printf("\nEntre the name of customer : ");
	   //	fgetc(stdin);
	   	fgets(name,50,stdin);
	   	name[strlen(name)-1] = 0;
	   		fp = fopen("RestaurantBill.dat","r");
	   	printf("\n ******Invoice of %s*****\n,name");
	   	
	   	while(fread(&order,sizeof(struct orders),1,fp)){
	   		float tot = 0;
	   		if(!strcmp(order.customer,name)){
	   		  generateBillHeaders(order.customer,order.date);
	   	
	   	for(int i = 0;i<order.numOfItems;i++){
	   		
	   		generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
	   		tot+= order.itm[i].qty*order.itm[i].price;
		   }
		   
	   	generateBillFooter(tot);
		   invoiceFound = 1;	
			   }
			   if(!invoiceFound){
			   	printf("Sorry the invoice for %s does not exists",name);
			   }
		   
	
	    
}
fclose(fp);
	   break;
	  
	   	case 4:
	   		printf("\n\t\t Bye Bye :");
	   		exit(0);
	   		break;
	   		
	   		 default:
	   		 	printf("Sorry Invalid options");
	   		 	break;
	   
	   }
	   printf("\nDo you want to perform another operations?[y/n] :");
   scanf("%s",&contFlag);

}
	   printf("\n\n");
	  
	

	
	
	
	
	return 0;
}
