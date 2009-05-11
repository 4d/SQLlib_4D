#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "../lib4d_sql/fourd.h"

int main(int argc, char **argv) 
{
	FOURD *cnx=NULL;
	FOURD_RESULT *res=NULL;
	FOURD_STATEMENT *state=NULL;
	FOURD_LONG val=10;
	printf("Debut du test!\n");
	cnx=fourd_init();
	if(fourd_connect(cnx,"127.0.0.2","SQL_User","SQL_User","base",19812)) {
		printf("Error %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
		fgetc(stdin);
		exit(1);
	}
	printf("connection ok!\n");
	/*printf("==================================================================\n");
	fgetc(stdin);
	if(query(cnx,3,"CREATE TABLE IF NOT EXISTS ACTEUR_FANS(ID INT32, Nom VARCHAR);")!=0) {
		printf("Error %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
	}
	else {
		char alias[512];
		char rtype[512];
		get(cnx->reponse,"Column-Aliases-Base64",alias,512);
		printf("Column-Aliases:%s\n",alias);
		get(cnx->reponse,"Result-Type",rtype,512);
		printf("Result-Type:%s\n",rtype);
		
	}*/
	printf("==================================================================\n");
	//fgetc(stdin);
	/*if(fourd_exec(cnx,"CREATE TABLE test (id int NOT NULL, val VARCHAR(255), PRIMARY KEY(id))")!=0)
	{
		printf("fourd_affected_rows:%d\n",fourd_affected_rows(cnx));
		printf("Error %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
	}
	//if(fourd_exec(cnx,"INSERT INTO ACTEUR_FANS(ID, Nom) VALUES(11,'PREMIERE INSERT');INSERT INTO ACTEUR_FANS(ID, Nom) VALUES(20,'DEUXIEME INSERT');INSERT INTO ACTEUR_FANS(ID, Nom) VALUES(30,'TROISIEME INSERT');")!=0)
	else  {
		printf("fourd_affected_rows:%d\n",fourd_affected_rows(cnx));
	} 
	if(fourd_exec(cnx,"UPDATE ACTEUR_FANS set Nom=concat('string ',Id);")!=0)
		
	//if(fourd_exec(cnx,"insert into ChampDate values(4,'14/02/09 14:56:00.000');")!=0)
	//if(fourd_query(cnx,"select ID,Nom from ACTEUR_FANS;")!=0)
	{
		printf("fourd_affected_rows:%d\n",fourd_affected_rows(cnx));
		printf("Error %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
	}
	else {
		printf("fourd_affected_rows:%d\n",fourd_affected_rows(cnx));
	}
	printf("==================================================================\n");
	 */
	/*fgetc(stdin);
	if((res=fourd_query(cnx,"select * from TableBig where ID<200;"))==NULL)	{
		printf("Error (%d):%s\n",fourd_errno(cnx),fourd_error(cnx));
	}
	else {
		int r=0;
		int nbCol=fourd_num_columns(res);
		printf("fourd_num_columns:%d\n",nbCol);
		printf("fourd_affected_rows:%d\n",fourd_affected_rows(cnx));
		printf("Nb row in result:%d\n",fourd_num_rows(res));
		printf("\n----------------------------------------------------------------------\n");
		printf(" \t\t\t");
		for(r=0;r<nbCol;r++) {
			printf("| %s (%s)\t",fourd_get_column_name(res,r),stringFromType(fourd_get_column_type(res,r)));
		}
		r=0;
		printf("\n----------------------------------------------------------------------\n");
		while(fourd_next_row(res)) {
			FOURD_STRING *str=NULL;
			//printf("L_%d\t\t\t| %d\t\t\t| ",r++,*fourd_field_long(res,0));
			char *value;int len;
			fourd_field_to_string(res,0,&value,&len);
			printf("L_%d\t\t\t| %s\t\t\t| ",r++,value);
			str=fourd_field_string(res,1);
			{
				int loc_i=0;
				for(loc_i=0;loc_i<str->length;loc_i++) {
					printf("%c%",str->data[loc_i*2]);
				}
			}
			printf("\n");
		}
	}
	printf("==================================================================\n");
	if(fourd_close_statement(res)) {
		printf("Error (%d):%s\n",fourd_errno(cnx),fourd_error(cnx));
	}*/
	//fgetc(stdin);
	//if((state=fourd_prepare_statement(cnx,"select ID,Nom from TableBig where ID=4 or ID=6;"))==NULL) {
	//if((state=fourd_prepare_statement(cnx,"select id,cTime from ChampTime"))==NULL) {
	//if((state=fourd_prepare_statement(cnx,"select id,cDate from ChampDate"))==NULL) {
	//if((state=fourd_prepare_statement(cnx,"select * from ChampImage"))==NULL) {
	if((state=fourd_prepare_statement(cnx,"SELECT * from _USER_TABLES"))==NULL) {
		printf("Error sur prepare %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
	}
	/*else if((val=5) && fourd_bind_param(state,0,VK_LONG, &val)) {
		printf("Error sur bind (%d):%s\n",fourd_errno(cnx),fourd_error(cnx));
	}
	else if((val=20) && fourd_bind_param(state,1,VK_LONG, &val)) {
		printf("Error sur bind (%d):%s\n",fourd_errno(cnx),fourd_error(cnx));
	}*/
	else if((res=fourd_exec_statement(state))==NULL)	{
		printf("Error sur exec %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
	}
	else {
		int r=0,c=0;
		int nbCol=fourd_num_columns(res);
		printf("fourd_num_columns:%d\n",nbCol);
		printf("fourd_affected_rows:%d\n",fourd_affected_rows(cnx));
		printf("Nb row in result:%d\n",fourd_num_rows(res));
		printf("\n----------------------------------------------------------------------\n");
		//printf(" \t\t\t");
		for(r=0;r<nbCol;r++) {
			printf("| %s (%s)\t",fourd_get_column_name(res,r),stringFromType(fourd_get_column_type(res,r)));
		}
		r=0;
		printf("\n----------------------------------------------------------------------\n");
		while(fourd_next_row(res)) {
			FOURD_TYPE type=VK_UNKNOW;
			FOURD_STRING *str=NULL;
			//printf("L_%d\t\t\t| %d\t\t\t| ",r++,*fourd_field_long(res,0));
			char *value;int len;
			//printf("L_%d\t\t\t| ",r++);
			for(c=0;c<nbCol;c++){
				type=fourd_get_column_type(res,c);
				switch(type){
					case VK_STRING:
						fourd_field_to_string(res,c,&value,&len);
						{
							int loc_i=0;
							for(loc_i=0;loc_i<len;loc_i+=2) {
								printf("%c%",value[loc_i]);
							}
							printf("\t\t| ");
						}						
						break;
					case VK_BLOB:
					case VK_IMAGE:
						//printf("fourd_field avant\n");
						
						{
							FOURD_BLOB *b=fourd_field(res,c);
							if(b!=NULL) {
								printf("Blob (%d bytes)\t| ",b->length);
							}else {
								printf("Null\t\t\t| ");
							}
						}
						break;
					default:
						fourd_field_to_string(res,c,&value,&len);
						
						printf("%s\t\t| ",value);
						break;
				}
				//free(value);
			}
			printf("\n");
			/*fourd_field_to_string(res,0,&value,&len);
			printf("L_%d\t\t\t| %s\t\t\t| ",r++,value);
			free(value);
			fourd_field_to_string(res,1,&value,&len);
			//str=fourd_field_string(res,1);
			{
				int loc_i=0;
				for(loc_i=0;loc_i<len;loc_i++) {
					printf("%c%",value[loc_i*2]);
				}
			}
			printf("\n");*/
		}
	}
	printf("==================================================================\n");
	if(fourd_close_statement(res)) {
		printf("Error %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
	}
	
	fgetc(stdin);
	if(fourd_close(cnx)) {
		printf("Error %s (%d):%s\n",fourd_sqlstate(cnx),fourd_errno(cnx),fourd_error(cnx));
	}
	fourd_free(cnx);
	printf("Déconnecter.......\n");
	fgetc(stdin);
    return 0;
}
