#include "query_string.h"

Get_Parameter_Status getParameter(const char* queryString, const char* parameterName, char* value) {
    char* temp = NULL;
    temp = strstr(queryString, parameterName);
    if (temp == NULL)
        return GP_ERR;
    temp = temp + strlen(parameterName);
    int i = 0;
    while (temp[i] != '&' && temp[i] != '\0') {
        value[i] = temp[i];
        i++;
    }
    value[i] = '\0';
    return GP_OK;
}