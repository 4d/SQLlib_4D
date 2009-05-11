#include "fourd.h"
#include "fourd_int.h"
#include "base64.h"
#include <string.h>




int socket_connect(FOURD *cnx,const char *host,unsigned int port)
{
	//WSADATA wsaData;
	
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;
	int iResult=0;
	//SOCKET ConnectSocket = INVALID_SOCKET;

	char sport[50];
	sprintf_s(sport,50,"%d",port);

	/*
	// Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        Printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
	*/

	//initialize Hints
	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(host, sport, &hints, &result);
	if ( iResult != 0 ) {
		Printf("getaddrinfo failed: %d : %s\n", iResult,gai_strerror(iResult));
		cnx->error_code=-iResult;
		strncpy_s(cnx->error_string,2048,gai_strerror(iResult),2048);
		return 1;
	}
	//Printf("getaddrinfo ok\n");

		
	// Attempt to connect to the first address returned by
	// the call to getaddrinfo
	ptr=result;

	// Create a SOCKET for connecting to server
	cnx->socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (cnx->socket == INVALID_SOCKET) {
		Printf("Error at socket(): %ld\n", WSAGetLastError());
		cnx->error_code=-WSAGetLastError();
		strncpy_s(cnx->error_string,2048,"Unable to create socket",2048);
		freeaddrinfo(result);
		return 1;
	}
	//Printf("Socket Ok\n");
	// Connect to server.
	iResult = connect( cnx->socket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		Printf("Error at socket(): %ld\n", WSAGetLastError());
		cnx->error_code=-WSAGetLastError();
		strncpy_s(cnx->error_string,2048,"Unable to connect to server",2048);
		freeaddrinfo(result);
		closesocket(cnx->socket);
		cnx->socket = INVALID_SOCKET;
		return 1;
	}
	//Printf("Connexion ok\n");



	
	// Should really try the next address returned by getaddrinfo
	// if the connect call failed
	// But for this simple example we just free the resources
	// returned by getaddrinfo and print an error message

	freeaddrinfo(result);

	if (cnx->socket == INVALID_SOCKET) {
		Printf("Unable to connect to server!\n");
		cnx->error_code=-1;
		strncpy_s(cnx->error_string,2048,"Unable to connect to server",2048);
		return 1;
	}
	//Printf("fin de la fonction\n");

	return 0;
}

void socket_disconnect(FOURD *cnx)
{
	int iResult=0;
	// shutdown the send half of the connection since no more data will be sent
	#ifdef WIN32
	iResult = shutdown(cnx->socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		Printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(cnx->socket);
		cnx->connected=0;
		return ;
	}
	#endif
	closesocket(cnx->socket);
	cnx->connected=0;
	//Printf("Disconnect ok\n");
}
int socket_send(FOURD *cnx,const char*msg)
{
	int iResult;
	//Printf("Send-len:%d\n",strlen(msg))
	Printf("Send:\n%s",msg);
	// Send an initial buffer
	iResult = send( cnx->socket, msg, (int)strlen(msg), 0 );
	if (iResult == SOCKET_ERROR) {
		Printf("send failed: %d\n", WSAGetLastError());
		socket_disconnect(cnx);
		return 1;
	}
	return 0;
}
int socket_send_data(FOURD *cnx,const char*msg,int len)
{
	int iResult;
	Printf("Send:%d bytes\n",len);
	PrintData(msg,len);
	Printf("\n");
	// Send an initial buffer
	iResult = send( cnx->socket, msg, len, 0 );
	if (iResult == SOCKET_ERROR) {
		Printf("send failed: %d\n", WSAGetLastError());
		socket_disconnect(cnx);
		return 1;
	}
	return 0;
}

int socket_receiv_header(FOURD *cnx,FOURD_RESULT *state)
{
	int iResult=0;
	int offset=0;
	int len=0;
	int crlf=0;
	char *fin_header=NULL;
	//read the HEADER only
	do 
	{
		offset+=iResult;
		iResult = recv(cnx->socket,state->header+offset,1, 0);
		len+=iResult;
		if(len>3)
		{
			if(state->header[offset-3]=='\r'
			 &&state->header[offset-2]=='\n'
			 &&state->header[offset-1]=='\r'
			 &&state->header[offset  ]=='\n')
			 crlf=1;
		}

	}while(iResult>0 && !crlf);
	if(!crlf)
	{
		Printf("Error: Header-end not found\n");
		return 1;
	}
	state->header[len]=0;
	state->header_size=len;
	Printf("Receiv:\n%s",state->header);
	//there we must add reading data
	//before analyse header 
	//see COLUMN-TYPES section
	return 0;
}
int socket_receiv_data(FOURD *cnx,FOURD_RESULT *state)
{
	int iResult=0;
	int offset=0;
	int len=0;
	int end_row=0;
	unsigned int nbCol=state->row_type.nbColumn;
	unsigned int nbRow=state->row_count_sent;
	unsigned int r,c;
	FOURD_TYPE *colType;
	FOURD_ELEMENT *pElmt=NULL;
	char status_code=0;
	int elmt_size=0;
	int elmts_offset=0;
	Printf("---Debut de socket_receiv_data\n");
	colType=calloc(nbCol,sizeof(FOURD_TYPE));
	//bufferize Column type
	for(c=0;c<state->row_type.nbColumn;c++)
		colType[c]=state->row_type.Column[c].type;

	/* allocate nbElmt in state->elmt */
	state->elmt=calloc(nbCol*nbRow,sizeof(FOURD_ELEMENT));
	
	Printf("Debut de socket_receiv_data\n");
	Printf("state->row_count:%d\t\tstate->row_count_sent:%d\n",state->row_count,state->row_count_sent);
	Printf("NbRow to read: %d\n",nbRow);
	/* read all row */
	for(r=0;r<nbRow;r++)
	{
		/* read status_code and row_id */
		if(state->updateability)  /* rowId is send only if row updateablisity */
		{
			int row_id=0;
			iResult = recv(cnx->socket,&status_code,sizeof(status_code), 0);
			//Printf("status_code for row:0x%X\n",status_code);
			len+=iResult;
			switch(status_code)
			{
			case '0':
				break;
			case '1':
				/* pElmt->elmt=calloc(vk_sizeof(colType[0]),1); */
				iResult = recv(cnx->socket,(char*)&row_id,sizeof(row_id), 0);
				/* Printf("row_id:%d\n",row_id); */
				len+=iResult;
				break;
			case '2':
				Printferr("Error during reading data\n");
				iResult = recv(cnx->socket,(char*)&(state->error_code),sizeof(state->error_code), 0);
				len+=iResult;
				return 1;	/* return on error */
				break;
			default:
				Printferr("Status code 0x%X not supported in data\n",status_code);
				break;
			}
		}
		else {
			Printf("Not read rowid\n");
		}
		/* read all columns */
		for(c=0;c<nbCol;c++,elmts_offset++)
		{
			pElmt=&(state->elmt[elmts_offset]);
			pElmt->type=colType[c];

			//read column status code
			iResult = recv(cnx->socket,&status_code,1, 0);
			len+=iResult;
			switch(status_code)
			{
			case '2'://error
				Printferr("Error during reading data\n");
				iResult = recv(cnx->socket,(char*)&(state->error_code),sizeof(state->error_code), 0);
				len+=iResult;
				return 1;//on sort en erreur
				break;
			case '0'://null value
				Printf("Read null value\n");
				pElmt->null=1;
				break;
			case '1'://value
				pElmt->null=0;
				switch(colType[c])
				{
				case VK_BOOLEAN:
				case VK_BYTE:
				case VK_WORD:
				case VK_LONG:
				case VK_LONG8:
				case VK_REAL:
				case VK_DURATION:
					pElmt->pValue=calloc(vk_sizeof(colType[c]),1);
					iResult = recv(cnx->socket,(pElmt->pValue),vk_sizeof(colType[c]), 0);
					len+=iResult;
					//Printf("Long: %d\n",*((int*)pElmt->pValue));
					break;
				case VK_TIMESTAMP:
					{
						FOURD_TIMESTAMP *tmp;
						tmp=calloc(sizeof(FOURD_TIMESTAMP),1);
						pElmt->pValue=tmp;
						iResult = recv(cnx->socket,(char*)&(tmp->year),sizeof(short), 0);
						len+=iResult;
						iResult = recv(cnx->socket,&(tmp->mounth),sizeof(char), 0);
						len+=iResult;
						iResult = recv(cnx->socket,&(tmp->day),sizeof(char), 0);
						len+=iResult;
						iResult = recv(cnx->socket,(char*)&(tmp->milli),sizeof(unsigned int), 0);
						len+=iResult;
					}
					break;
				case VK_FLOAT:
					{
						//int exp;char sign;int data_length;void* data;
						FOURD_FLOAT *tmp;
						tmp=calloc(sizeof(FOURD_FLOAT),1);
						pElmt->pValue=tmp;

						iResult = recv(cnx->socket,(char*)&(tmp->exp),sizeof(int), 0);
						len+=iResult;
						iResult = recv(cnx->socket,&(tmp->sign),sizeof(char), 0);
						len+=iResult;
						iResult = recv(cnx->socket,(char*)&(tmp->data_length),sizeof(int), 0);
						len+=iResult;
						iResult = recv(cnx->socket,(tmp->data),tmp->data_length, 0);
						len+=iResult;

						//Printferr("Float not supported\n");
					}
					break;
				case VK_STRING:
					{
						int data_length=0;
						FOURD_STRING *str;
						//read negative value of length of string
						str=calloc(1,sizeof(FOURD_STRING));
						pElmt->pValue=str;					
						iResult = recv(cnx->socket,(char*)&data_length,4, 0);
						len+=iResult;
						data_length=-data_length;
						//Printf("Size of String: %d\n",data_length);
						str->length=data_length;
						str->data=calloc(1,data_length*2+2);
						iResult = recv(cnx->socket,(str->data),(data_length*2), 0);
						str->data[data_length*2]=0;
						str->data[data_length*2+1]=0;
						len+=iResult;
						/*
						{
							int length=0;
							char *chaine=NULL;
							chaine=base64_encode((unsigned char*)str->data,data_length*2,&length);
							Printf("Chaine: %s\n",chaine);
							free(chaine);
						}*/
					}
					break;
				case VK_IMAGE:
					//Printferr("Image-Type not supported\n");
					//break;
				case VK_BLOB:
					{
						int data_length=0;
						FOURD_BLOB *blob;
						//read negative value of length of string
						blob=calloc(1,sizeof(FOURD_BLOB));
						pElmt->pValue=blob;
						iResult = recv(cnx->socket,(char*)&data_length,4, 0);
						len+=iResult;
						blob->length=data_length;
						blob->data=calloc(1,data_length);
						iResult = recv(cnx->socket,blob->data,data_length, 0);
						len+=iResult;
						//Printf("Blob: %d Bytes\n",data_length);
					}
					Printferr("Blob not supported\n");
					break;
				default:
					Printferr("Type not supported (%s)\n",stringFromType(colType[c]));
					break;
				}
				break;
			default:
				Printferr("Status code 0x%X not supported in data\n",status_code);
				break;
			}
		}
	}
	Printf("---Fin de socket_receiv_data\n");
	return 0;
}
int socket_receiv_update_count(FOURD *cnx,FOURD_RESULT *state)
{
	FOURD_LONG8 data=0;
	int iResult=0;
	int len=0;
	iResult = recv(cnx->socket,(char*)&data,8, 0);
	len+=iResult;
	Printf("Ox%X\n",data);
	cnx->updated_row=data;
	Printf("\n");

	return 0;
}