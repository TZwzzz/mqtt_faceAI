#pragma once
extern "C"
{
typedef const char * (*PTR_FunCallback) (const char *uri,const char *aiType);
void Init(PTR_FunCallback callback,const char **pszCapabilities,int size);

}


