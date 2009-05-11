#include <stdio.h>
#include <string.h>

extern int Printf(const char* format,...);
extern int Printferr(const char* format,...);
#include "fourd.h"
FOURD_TYPE typeFromString(const char *type)
{
	if(strcmp(type,"VK_BOOLEAN")==0)
		return VK_BOOLEAN;  
	if(strcmp(type,"VK_BYTE")==0)
		return VK_BYTE;       
	if(strcmp(type,"VK_WORD")==0)
		return VK_WORD;      
	if(strcmp(type,"VK_LONG")==0)
		return VK_LONG;       
	if(strcmp(type,"VK_LONG8")==0)
		return VK_LONG8;      
	if(strcmp(type,"VK_REAL")==0)
		return VK_REAL;       
	if(strcmp(type,"VK_FLOAT")==0)
		return VK_FLOAT;      
	if(strcmp(type,"VK_TIMESTAMP")==0)
		return VK_TIMESTAMP;  
	if(strcmp(type,"VK_TIME")==0)
		return VK_TIMESTAMP;  
	if(strcmp(type,"VK_DURATION")==0)
		return VK_DURATION;   
	if(strcmp(type,"VK_TEXT")==0)
		return VK_STRING;     
	if(strcmp(type,"VK_STRING")==0)
		return VK_STRING;     
	if(strcmp(type,"VK_BLOB")==0)
		return VK_BLOB;       
	if(strcmp(type,"VK_IMAGE")==0)
		return VK_IMAGE;      
	return VK_UNKNOW;
}
const char* stringFromType(FOURD_TYPE type)
{
	switch(type)
	{
	case VK_BOOLEAN:
		return "VK_BOOLEAN";
	case VK_BYTE:
		return "VK_BYTE";
	case VK_WORD:
		return "VK_WORD";
	case VK_LONG:
		return "VK_LONG";
	case VK_LONG8:
		return "VK_LONG8";
	case VK_REAL:
		return "VK_REAL";
	case VK_FLOAT:
		return "VK_FLOAT";
	case VK_TIMESTAMP:
		return "VK_TIMESTAMP";
	case VK_TIME:
		return "VK_TIME";
	case VK_DURATION:
		return "VK_DURATION";
	case VK_STRING:
		return "VK_STRING";
	case VK_BLOB:
		return "VK_BLOB";
	case VK_IMAGE:
		return "VK_IMAGE";
	default:
		return "VK_UNKNOW";
		break;
	}
}
/******************************************************************/
/* vk_sizeof                                                      */
/******************************************************************/
/* return sizeof type or -1 if varying length or 0 if unknow type */
/******************************************************************/
int vk_sizeof(FOURD_TYPE type)
{
	switch(type)
	{
	case VK_BOOLEAN:
	case VK_BYTE:
	case VK_WORD:
		return 2;
		break;
	case VK_LONG:
		return 4;
		break;
	case VK_LONG8:
	case VK_REAL:
	case VK_DURATION:
		return 8;
		break;
	case VK_FLOAT:
		//Varying length
		return -1;
		break;
	case VK_TIME:
	case VK_TIMESTAMP:	
		return 8;
		break;
	case VK_TEXT:
	case VK_STRING:
	case VK_BLOB:
	case VK_IMAGE:
		//Varying length
		return -1;
		break;
	}
	//error type not found
	Printf("Error: Unknow type in vk_sizeof function\n");
	return 0;
}

FOURD_RESULT_TYPE resultTypeFromString(const char *type)
{
	if(strcmp(type,"Update-Count")==0)
		return UPDATE_COUNT; 
	if(strcmp(type,"Result-Set")==0)
		return RESULT_SET; 
	return UNKNOW;
}
const char* stringFromResultType(FOURD_RESULT_TYPE type)
{
	switch(type)
	{
	case UPDATE_COUNT:
		return "Update-Count";
		break;
	case RESULT_SET:
		return "Result-Set";
		break;
	}
	return "Unknow";
}