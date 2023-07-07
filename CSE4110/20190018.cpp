#include <stdio.h>
#include <string.h>
#include "mysql.h"
#include<iostream>
#define MAX 1024
#pragma comment(lib, "libmysql.lib")
#pragma warning(disable : 4996)

const char* host = "localhost";
const char* user = "root";
const char* pw = "s20190018";
const char* db = "project";
using namespace std;
char line[MAX];
FILE* fp;
int table_num;
int tuple_num;
int num = 0;
MYSQL* connection = NULL;

int initialize_DB()
{
	/*
	txt파일로부터 DB를 초기화하는 함수이다.
	*/
	char* query;
	int state = 0;
	int i;
	table_num = atoi(fgets(line, MAX, fp)); // table 개수
	tuple_num = atoi(fgets(line, MAX, fp)); // tuple 개수
	state = mysql_query(connection, "delete from customer");
	state = mysql_query(connection, "delete from buy");
	state = mysql_query(connection, "delete from product");
	state = mysql_query(connection, "delete from product_pack");
	state = mysql_query(connection, "delete from shipment");
	state = mysql_query(connection, "delete from delivered");
	state = mysql_query(connection, "delete from warehouse");
	state = mysql_query(connection, "delete from sell");
	state = mysql_query(connection, "delete from stock");
	state = mysql_query(connection, "delete from send");
	state = mysql_query(connection, "delete from store");
	state = mysql_query(connection, "delete from manufacturer");
	state = mysql_query(connection, "delete from supply");
	state = mysql_query(connection, "delete from headoffice");
	state = mysql_query(connection, "delete from onlineamount");
	state = mysql_query(connection, "delete from supplement");
	state = mysql_query(connection, "drop table if exists customer");
	state = mysql_query(connection, "drop table if exists supplement");
	state = mysql_query(connection, "drop table if exists buy");
	state = mysql_query(connection, "drop table if exists product");
	state = mysql_query(connection, "drop table if exists product_pack");
	state = mysql_query(connection, "drop table if exists shipment");
	state = mysql_query(connection, "drop table if exists delivered");
	state = mysql_query(connection, "drop table if exists warehouse");
	state = mysql_query(connection, "drop table if exists sell");
	state = mysql_query(connection, "drop table if exists stock");
	state = mysql_query(connection, "drop table if exists send");
	state = mysql_query(connection, "drop table if exists store");
	state = mysql_query(connection, "drop table if exists manufacturer");
	state = mysql_query(connection, "drop table if exists supply");
	state = mysql_query(connection, "drop table if exists headoffice");
	state = mysql_query(connection, "drop table if exists onlineamount");
	// create needed tables
	for (i = 0; i < table_num; i++)
	{
		query = fgets(line, MAX, fp);
		state = mysql_query(connection, query); // return 0 if the statement was successful
		puts(query);
		if (state != 0)
		{
			printf("CREATE TABLE ERROR: %s\n", query);
			return 1;
		}
	}

	// insert tuples
	for (i = 0; i < tuple_num; i++)
	{
		query = fgets(line, MAX, fp);
		state = mysql_query(connection, query);
		puts(query);
		if (state != 0)
		{
			printf("INSERT ERROR: %s\n", query);
			return 1;
		}
	}

	return 0;
}

int drop_tables()
{
	/*
	생성한 테이블의 tuple을 모두 지우고 테이블을 drop 한다.
	*/
	char* query;
	int state = 0;
	int i;

	// drop tables
	for (i = 0; i < 2 * table_num + 2; i++)
	{
		// first query: SET FOREIGN_KEY_CHECKS = 0
		// last query: SET FOREIGN_KEY_CHECKS = 1
		query = fgets(line, MAX, fp);
		state = mysql_query(connection, query);
		if (state != 0)
		{
			printf("DROP TABLE ERROR: %s\n", query);
			return 1;
		}
	}

	return 0;
}

void clrscr() {
	system("cls||clear");
}

void type1(int type, char* tracking) {
	//printf("type1\n");
	char query1[2024];
	int state1 = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	
	switch (type) {
	case 0:
		//printf("type1\n");
		// shipped by USPS with tracking number X destroyed in an accident.
		// the contact information for the customer.
		getchar();
		MYSQL_RES* sql_result;
		MYSQL_ROW sql_row;
		sprintf(query1, "select ship.tracking_num, cus.customer_id, cus.name, cus.phone from shipment as ship join customer as cus using(customer_id) where shipper_name='USPS' and current_state='missing'");
		//state = 0;
		state1 = mysql_query(connection, query1);
		//cout << state1 << " ";
		
		if (state1 == 0) {
			sql_result = mysql_store_result(connection);
			printf("The package shipped by USPS is reported to have beendestoryed.\n");
			printf("The contact information for the customer.\n");
			printf("     %10s     %10s     %13s     %13s\n", "tracking_num", "customer_id", "customer_name", "phone_number");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				num++;
				printf("     %10s     %10s     %13s     %13s\n", sql_row[0],sql_row[1], sql_row[2], sql_row[3]);
			}
			mysql_free_result(sql_result);
		}
		break;
	case 1:
		//printf("type1-1\n");
		printf("Find the contents of that shipment and create a new shipment of replacement items.\n");
		//getchar();
		//sprintf(query1, "INSERT INTO delivered (tracking_num, product_id) select ship.tracking_num+1, del.product_id from shipment as ship join delivered as del using (tracking_num) where shipper_name='USPS' and current_state='missing'");
		//sprintf(query1, "select max(tracking_num)+1, ship.customer_id from shipment as ship join delivered as del using (tracking_num) where shipper_name='USPS' and current_state='missing'");
		/*
		sprintf(query1, "select ship.tracking_num+1, del.product_id from shipment as ship join delivered as del using (tracking_num) where shipper_name='USPS' and current_state='missing'");
		state1 = mysql_query(connection, query1);
		//puts(query1);
		if (state1 == 0) {
			sql_result = mysql_store_result(connection);
			printf("the contents of that shipment\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s\n", sql_row[0], sql_row[1]);
			}
			mysql_free_result(sql_result);
		}
		
		sprintf(query1, "select ship.tracking_num+1, '00011', ship.customer_id, 'USPS', 'preparing', date_add(now(), interval 7 day) from shipment as ship join delivered as del using (tracking_num) where shipper_name='USPS' and current_state='missing'");
		state1 = mysql_query(connection, query1);
		//puts(query1);
		if (state1 == 0) {
			printf("create a new shipment of replacement items.\n");
			sql_result = mysql_store_result(connection);
			printf("     %10s     %10s     %10s     %10s     %10s     %10s\n", "tracking_num", "product_id", "customer_id", "shipper", "current", "promised");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s     %10s     %10s     %10s     %10s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5]);
			}
			mysql_free_result(sql_result);
		}*/
		break;
	default:
		break;
	}
	return;
}

void type2(int type) {
	//printf("type2\n");
	char query2[2024];
	int state = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	switch (type) {
	case 0:
		//printf("type2\n");
		//customer bought the most (by price) in the past year

		sprintf(query2, "select cus.customer_id, cus.name, case cus.period when 'regular' then cus.amount*12 else sum(buy.prices) end as SUM from buy join customer as cus using (customer_id) where YEAR(buy_date)=YEAR(date_add(now(), interval -1 year)) group by customer_id order by SUM desc limit 1");
		//sprintf(query2, "select cus.customer_id, case cus.period when 'regular' then cus.amount*12 else select(sum(buy.prices) from buy group by customer_id having buy.customer_id=cus.customer_id) end as SUM from customer as cus");
		//where (cus.start_pay is not null or YEAR(cus.start_pay)!=YEAR(now()))
		//state = 0;
		state = mysql_query(connection, query2);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("The customer bought the most (by price) in the past year.\n");
			printf("     %10s     %10s     %13s\n", "customer_id", "customer_name","purchase amount");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
			}
			mysql_free_result(sql_result);
		}
		break;
	case 1:
		//printf("type2-1\n");
		// product that the customer bought the most.
		sprintf(query2, "with t as (select cus.customer_id as CI, cus.name, case cus.period when 'regular' then cus.amount*(12) else sum(buy.prices) end as SUM from buy join customer as cus using (customer_id) where YEAR(buy_date)=YEAR(date_add(now(), interval -1 year)) group by customer_id order by SUM desc limit 1) select product_id, sum(buy.sales) as SUM from buy join t on t.CI=buy.customer_id group by buy.product_id order by SUM limit 1");
		state = mysql_query(connection, query2);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("The customer bought the most (by price) in the past year.\n");
			printf("     %10s     %10s\n", "product_id", "unit-sales");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s\n", sql_row[0], sql_row[1]);
			}
			mysql_free_result(sql_result);
		}
		break;
	default:
		break;
	}
	
	
	return;
}

void type3(int type, int k) {
	//printf("type3\n");
	char query3[2024];
	int state = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	//printf("type3\n");
	//all products sold in the past year.
	//getchar();
	
	switch (type) {
	case 0:
		printf("There are all products sold in the past year.\n");
		sprintf(query3, "select buy.product_id, pro.product_name, sum(buy.prices) as SUM from buy join product as pro using (product_id) where YEAR(buy_date)=YEAR(date_add(now(), interval -1 year)) group by buy.product_id order by SUM desc");
		state = mysql_query(connection, query3);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("The customer bought the most (by price) in the past year.\n");
			printf("     %10s     %10s    %10s\n", "product_id", "product_name", "accumulative");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
			}
			mysql_free_result(sql_result);
		}
		break;
	case 1:
		//printf("type3-1\n");
		//the top k products by dollar-amount sold.
		printf(" the top k products by dollar-amount sold.\n");
		sprintf(query3, "select buy.product_id, pro.product_name, sum(buy.prices) as SUM from buy join product as pro using (product_id) where YEAR(buy_date)=YEAR(date_add(now(), interval -1 year)) group by buy.product_id order by SUM desc limit %d", k);
		state = mysql_query(connection, query3);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("The customer bought the most (by price) in the past year.\n");
			printf("     %10s     %10s    %10s\n", "product_id", "product_name", "dollars-amount");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
			}
			mysql_free_result(sql_result);
		}
		break;
	case 2:
		//printf("type3-2\n");3
		//the top 10% products by dollar-amount sold. 
		sprintf(query3, "with t as (select buy.product_id as PI, pro.product_name PN, sum(buy.prices) as SUM from buy join product as pro using (product_id) where YEAR(buy_date)=YEAR(date_add(now(), interval -1 year)) group by pro.product_id) select ranked.PI, ranked.PN, ranked.SUM from (select PI, PN, SUM, percent_rank() over (order by SUM) as rk from t) as ranked where ranked.rk>=0.9 order by ranked.SUM desc");
		//(select PI, PN, SUM, percent_rank() over (order by SUM) as rk from t) as rancked order by SUM desc
		//sprintf(query3, "select buy.product_id as PI, pro.product_name PN, sum(buy.prices) as SUM, count(*) as CNT from buy join product as pro using (product_id) group by pro.product_id");
		state = mysql_query(connection, query3);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("the top 10 percent products by dollar-amount sold. \n");
			printf("     %10s     %10s    %10s\n", "product_id", "product_name", "dollars-amount");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
			}
			mysql_free_result(sql_result);
		}
		break;
	default:
		break;
	}
	return;
}

void type4(int type, int k) {
	//printf("type4\n");
	char query4[2024];
	char char_k[10];
	sprintf(char_k, "%d", k);
	int state = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	switch (type) {
	case 0:
		//printf("type4\n");
		// all products by unit sales in the past year. 
		printf("There are all products sold in the past year.\n");		
		sprintf(query4, "select buy.product_id, pro.product_name, sum(buy.sales) as SUM from buy join product as pro using (product_id) where YEAR(buy_date)=YEAR(date_add(now(), interval -1 year)) group by buy.product_id order by SUM desc");

		state = mysql_query(connection, query4);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("The customer bought the most (by price) in the past year.\n");
			printf("     %10s     %15s     %10s\n", "product_id", "product_name", "sales_unit");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %15s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
			}
			mysql_free_result(sql_result);
		}
		break;
	case 1:
		//printf("type4-1\n");
		// the top k products by unit sales.
		printf("The top k products by unit sales.\n");
		sprintf(query4, "select buy.product_id, pro.product_name, sum(buy.sales) as SUM from buy join product as pro using (product_id) where YEAR(buy_date)=YEAR(date_add(now(), interval -1 year)) group by buy.product_id order by SUM desc limit %d", k);
		state = mysql_query(connection, query4);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			//printf("The customer bought the most (by price) in the past year.\n");
			printf("     %10s     %15s     %10s\n", "product_id", "product_name", "sales_unit");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %15s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
			}
			mysql_free_result(sql_result);
		}
		break;
	case 2:
		//printf("type4-2\n");
		//find the top 10% products by unit sales.
		
		sprintf(query4, "with t as (select buy.product_id as PI, pro.product_name as PN, sum(buy.sales) as SUM from buy join product as pro using (product_id) where YEAR(buy.buy_date)=YEAR(date_add(now(), interval -1 year)) group by buy.product_id) select PI, PN, SUM from (select PI, PN, SUM, percent_rank() over (order by SUM) as rk from t) as ranked where ranked.rk>=0.9 order by ranked.SUM desc");
		state = mysql_query(connection, query4);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("the top 10% products by dollar-amount sold. \n");
			printf("     %10s     %10s    %10s\n", "product_id", "product_name", "unit-sales");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				printf("     %10s     %10s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
			}
			mysql_free_result(sql_result);
		}
		break;
		break;
	default:
		break;
	}
	return;

}

void type5() {
	//printf("type5\n");
	// products out-of-stock at every store in California.

	char query5[2024];
	int state = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	sprintf(query5,"select store_id, product_id, product_name from (stock join store using(store_id)) join product using (product_id) where store_location = 'California' ");
	state = mysql_query(connection, query5);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("There are products that are out-of-stock at every store in California\n");
		printf("     %10s      %10s      %10s\n", "store_id", "product_id", "product_name");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("     %10s      %10s     %10s\n", sql_row[0], sql_row[1], sql_row[2]);
		}
		mysql_free_result(sql_result);
	}
}

void type6() {
	//printf("type6\n");
	// packages that were not delivered within the promised time.
	char query6[2024];
	int state = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	sprintf(query6, "select tracking_num, product_id, product_name from (delivered join shipment using(tracking_num)) join product using(product_id) where promised_date != delivered_date and current_state='completed'");
	state = mysql_query(connection, query6);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("packages that were not delivered within the promised time.\n");
		printf("     %10s      %10s      %10s\n", "tracking_num", "product_id", "product_name");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("     %10s      %10s      %10s\n", sql_row[0], sql_row[1], sql_row[2]);
		}
		mysql_free_result(sql_result);
	}
}

void type7() {
	//printf("type7\n");
	// the bill for each customer for the past month.
	char query7[2024];
	int state = 0;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	sprintf(query7, "with t as (select cus.customer_id, case cus.period when 'regular' then cus.amount else sum(buy.prices) end as SUM from buy join customer as cus using (customer_id) where MONTH(buy_date)=MONTH(date_add(now(), interval -1 month)) and YEAR(buy_date)=YEAR(now()) group by customer_id) select t2.CI, ifnull(t2.bill, 0) from (select customer_id as CI, case period when 'regular' then amount else t.SUM end as bill from customer natural left join t) as t2");
	state = mysql_query(connection, query7);
	if (state == 0) {
		sql_result = mysql_store_result(connection);
		printf("     %10s      %10s\n","customer_id", "bill for the past month");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
			printf("     %10s      %10s\n", sql_row[0], sql_row[1]);
		}
		mysql_free_result(sql_result);
	}
	
}


void show_interface() {
	//clrscr();
	while (1) {
		int choice = -1;
		int subC = -1;
		int quit = 1;
		int k = -1;
		int end = 0;
		char tracking[5];

		printf("\n------- SELECT QUERY TYPES -------\n\n");
		printf("\t1. TYPE 1\n");
		printf("\t2. TYPE 2\n");
		printf("\t3. TYPE 3\n");
		printf("\t4. TYPE 4\n");
		printf("\t5. TYPE 5\n");
		printf("\t6. TYPE 6\n");
		printf("\t7. TYPE 7\n");
		printf("\t0. QUIT\n");
		printf("----------------------------------\n");
		printf("\nSelect type: ");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			end = 1;
			break;
		case 1:
			while (1) {
				clrscr();
				printf("\n---------- TYPE 1 ----------\n\n");
				type1(0, tracking);
				printf("\n---------- Subtypes in TYPE 1 ----------\n");
				printf("1. TYPE 1-1\n");
				printf("\nSelect type ('0': back to select menu) : ");
				//getchar();
				scanf("%d", &subC);

				while ((subC != 0) && (subC != 1))
				{
					printf("\nThere is no type %d\nSelect type again : ", subC);
					getchar();
					scanf("%d", &subC);
				}
				switch (subC)
				{
				case 1:
					while (1) {
						printf("\n---------- TYPE 1-1 ----------\n\n");
						printf("What is new tracking number? : ");
						getchar();
						scanf("%s", tracking);
						type1(1, tracking);
						printf("\nPut'0'to go back to select menu : ");
						getchar();
						scanf("%d", &quit);
						if (quit == 0)
						{
							clrscr();
							break;
						}
					}
					break;
				case 0:
					quit = 0;
					break;
				}
				if (quit == 0) {
					break;
				}
				break;
			}
			break;
		case 2:
			while (1) {
				clrscr();
				printf("\n---------- TYPE 2 ----------\n\n");
				type2(0);

				printf("\n---------- Subtypes in TYPE 2 ----------\n");
				printf("1. TYPE 2-1\n");
				printf("\nSelect type ('0': back to select menu) : ");
				getchar();
				scanf("%d", &subC);

				while ((subC != 0) && (subC != 1))
				{
					printf("\nThere is no type %d\nSelect type again : ", subC);
					getchar();
					scanf("%d", &subC);
				}
				switch (subC)
				{
				case 1:
					while (1) {
						printf("\n---------- TYPE 2-1 ----------\n\n");
						type2(1);
						printf("\nPut '0' to go back to select menu: ");
						getchar();
						scanf("%d", &quit);
						if (quit == 0)
						{
							clrscr();
							break;
						}
					}
					break;
				case 0:
					quit = 0;
					break;
				}
				if (quit == 0) {
					break;
				}
				break;
			}
			break;
		case 3:
			while (1) {
				clrscr();
				printf("\n---------- TYPE 3 ----------\n\n");
				type3(0, k);


				printf("\n---------- Subtypes in TYPE 3 ----------\n");
				printf("1. TYPE 3-1\n");
				printf("2. TYPE 3-2\n");
				printf("\nSelect type ('0': back to select menu) : ");
				getchar();
				scanf("%d", &subC);

				while ((subC != 0) && (subC != 1) && (subC != 2))
				{
					printf("\nThere is no type %d\nSelect type again : ", subC);
					getchar();
					scanf("%d", &subC);
				}
				switch (subC)
				{
				case 1:
					while (1) {
						printf("\n---------- TYPE 3-1 ----------\n\n");
						printf(" ** Find the top k brands by dollars_amount by the year **\n");
						printf("Which K? : ");
						getchar();
						scanf("%d", &k);
						type3(1, k);
						printf("\nPut '0' to go back to select menu: ");
						getchar();
						scanf("%d", &quit);
						if (quit == 0)
						{
							clrscr();
							break;
						}
					}
					break;
				case 2:
					while (1) {
						printf("\n---------- TYPE 3-2 ----------\n\n");
						type3(2, k);
						printf("\nPut '0' to go back to select menu: ");
						getchar();
						scanf("%d", &quit);
						if (quit == 0)
						{
							clrscr();
							break;
						}
					}
					break;
				case 0:
					quit = 0;
					break;
				}
				if (quit == 0) {
					break;
				}
				break;
			}
			break;
		case 4:
			while (1) {
				clrscr();
				printf("\n---------- TYPE 4 ----------\n\n");
				type4(0, k);


				printf("\n---------- Subtypes in TYPE 4 ----------\n");
				printf("1. TYPE 4-1\n");
				printf("2. TYPE 4-2\n");
				printf("\nSelect type ('0': back to select menu) : ");
				getchar();
				scanf("%d", &subC);

				while ((subC != 0) && (subC != 1) && (subC != 2))
				{
					printf("\nThere is no type %d\nSelect type again : ", subC);
					getchar();
					scanf("%d", &subC);
				}
				switch (subC)
				{
				case 1:
					while (1) {
						printf("\n---------- TYPE 4-1 ----------\n\n");
						printf(" ** Find the top k brands by unit sales by the year **\n");
						printf("Which K? : ");
						getchar();
						scanf("%d", &k);
						type4(1, k);
						printf("\nPut '0' to go back to select menu: ");
						getchar();
						scanf("%d", &quit);
						if (quit == 0)
						{
							clrscr();
							break;
						}
					}
					break;
				case 2:
					while (1) {
						printf("\n---------- TYPE 4-2 ----------\n\n");
						type4(2, k);
						printf("\nPut '0' to go back to select menu: ");
						getchar();
						scanf("%d", &quit);
						if (quit == 0)
						{
							clrscr();
							break;
						}
					}
					break;
				case 0:
					quit = 0;
					break;
				}
				if (quit == 0) {
					break;
				}
				break;
			}
			break;
		case 5:
			while (1) {
				clrscr();
				printf("\n---------- TYPE 5 ----------\n\n");
				type5();
				printf("\nPut '0' to go back to select menu: ");
				getchar();
				scanf("%d", &quit);
				if (quit == 0)
				{
					clrscr();
					break;
				}
			}
			break;
		case 6:
			while (1) {
				clrscr();
				printf("\n---------- TYPE 6 ----------\n\n");
				type6();
				printf("\nPut '0' to go back to select menu: ");
				getchar();
				scanf("%d", &quit);
				if (quit == 0)
				{
					clrscr();
					break;
				}
			}
			break;
		case 7:
			while (1) {
				clrscr();
				printf("\n---------- TYPE 7 ----------\n\n");
				type7();
				printf("\nPut '0' to go back to select menu: ");
				getchar();
				scanf("%d", &quit);
				if (quit == 0)
				{
					clrscr();
					break;
				}
			}
			break;
		default:
			clrscr();
			break;
		}

		if (end == 1) {
			break;
		}
	

	}
			
			
			
	return;

}

int main(void) {

	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR: %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}
	else
	{
		printf("Connection Succeed\n");
		
		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		int state = 0;
		
		fp = fopen("20190018.txt", "r");
		int initialized = initialize_DB();
		if (initialized != 0)
		{
			printf("Initialize DB ERROR\n");
			return 1;
		}
		show_interface();

		
		drop_tables();

		fclose(fp);
		mysql_close(connection);

	}


}





