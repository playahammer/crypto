#include "base64.h"


int
main(void)
{
      string teststr = "base64";
      string encoded = base64encode(teststr);
      string decoded = base64decode(encoded);
      cout<<"base64 encode:"<<encoded<<endl;
      cout<<"base64 decode:"<<decoded<<endl;
      return 0;
}