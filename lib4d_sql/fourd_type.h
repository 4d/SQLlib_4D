#ifndef __FOURD_TYPE__
#define __FOURD_TYPE__
typedef enum
{
	VK_UNKNOW=0,
	VK_BOOLEAN,
	VK_BYTE,
	VK_WORD,
	VK_LONG,
	VK_LONG8,
	VK_REAL,
	VK_FLOAT,
	VK_TIMESTAMP,
	VK_DURATION,
	VK_STRING,
	VK_BLOB,
	VK_IMAGE 
}FOURD_TYPE;
/******************************/
/* parse and format FOUR_TYPE */
/******************************/
FOURD_TYPE typeFromString(const char *type);
const char* stringFromType(FOURD_TYPE type);
/******************************************************************/
/* vk_sizeof                                                      */
/******************************************************************/
/* return sizeof type or -1 if varying length or 0 if unknow type */
/******************************************************************/
int vk_sizeof(FOURD_TYPE type);

/***************/
/* Result-Type */
/***************/
typedef enum
{
	UNKNOW=0,
	UPDATE_COUNT,
	RESULT_SET
}FOURD_RESULT_TYPE;
FOURD_RESULT_TYPE resultTypeFromString(const char *type);
const char* stringFromResultType(FOURD_RESULT_TYPE type);

/*********************/
/* Structure of VK_* */
/*********************/
typedef short FOURD_BOOLEAN;
typedef short FOURD_BYTE;
typedef short FOURD_WORD;
typedef	int FOURD_LONG;
typedef	__int64 FOURD_LONG8;
typedef	double FOURD_REAL;
typedef	struct{int exp;char sign;int data_length;void* data;}FOURD_FLOAT;
typedef	struct{short year;char mounth;char day;unsigned int milli;}FOURD_TIMESTAMP;
typedef	__int64 FOURD_DURATION;//in milliseconds
typedef	struct{int length;unsigned char *data;}FOURD_STRING;
typedef	struct{unsigned int length;void *data;}FOURD_BLOB;
//typedef	struct{}FOURD_IMAGE; 

#endif