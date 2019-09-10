#include "base64.h"


string 
base64encode(string input)
{
      const string base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefjhijklmnopqrstuvwxyz0123456789+/=";
      
      if (input.length() == 0) return NULL;
      int len = input.length() / 3;

      if (input.length() % 3 == 1) len += 4; // 8bits. two 6-bit groups, two pading
      else if (input.length() % 3 == 2) len += 4; // 16bits. there 6-bit groups, one padding.
      int index = 0;
      string encoded;
      
      int ven = 0;
      for (int i = 0; i < (input.length() / 3) * 3; i+=3)
      {
            u_int24_t group = ((u_int8_t)input[i] << 16) + ((u_int8_t)input[i + 1] << 8) + (u_int8_t)input[i + 2];
            
            for (int j = 0; j < 4; j++)
            {
                  int index = (group >> ((3 - j) * 6)) & BASE6BITS;
                  encoded.push_back(base[index]);
            }
      }

      // Padding

      if(input.length() % 3 == 1)
      {
            int cur = (u_int8_t)input[input.length() - 1] << 4;
            int cur1 = (cur >> 6) & BASE6BITS;
            encoded.push_back(base[cur1]);
            encoded.push_back(base[cur & BASE6BITS]);
            
            encoded.push_back(base[64]); // "=" padding
            encoded.push_back(base[64]);
      }

      else if (input.length() % 3 == 2)
      {
            int cur = ((u_int8_t)input[input.length() - 2] << 10) + ((u_int8_t)input[input.length() - 1] << 2);
            encoded.push_back(base[(cur >> 12) & BASE6BITS]);
            encoded.push_back(base[(cur >> 6) & BASE6BITS]);
            encoded.push_back(base[cur & BASE6BITS]);

            encoded.push_back(base[64]); // '=/' padding
      }


      return encoded;
}

string
base64decode(string input)
{

      if (input.length() == 0 || input.length() % 4 != 0) return NULL;


      int len = (input.length() / 4) * 3;
      if (input[input.length() - 1] == '=') len += 2;
      if (input[input.length() - 2] == '=') len --;

      string decoded;

      int ven = 0;

      int looplen = input[input.length() - 1] == '=' ? input.length() - 4 : input.length();
      for (int i = 0; i < looplen; i+=4)
      {
            u_int24_t group = (getindexbychar(input[i]) << 18) + (getindexbychar(input[i + 1]) << 12) + (getindexbychar(input[i + 2]) << 6) + getindexbychar(input[i + 3]);
            
            decoded.push_back((group >> 16) & BASE8BITS);
            decoded.push_back((group >> 8) & BASE8BITS);
            decoded.push_back(group & BASE8BITS);
      }



      if (input[input.length() - 1] == '=' && input[input.length() - 2] == '=') // two paddings
      {
            int cur = (getindexbychar(input[input.length() - 4]) << 2) + (getindexbychar(input[input.length() - 3]) >> 4);
            decoded.push_back(cur);
      }
      else if (input[input.length() - 1] == '=') // one padding
      {
            int cur = (getindexbychar(input[input.length() - 4]) << 10) + (getindexbychar(input[input.length() - 3]) << 4) + (getindexbychar(input[input.length() - 2]) >> 2);
            cout<<cur<<endl;
            cout<<((cur >> 8) & BASE8BITS)<<endl;
            decoded.push_back((cur >> 8) & BASE8BITS);
            decoded.push_back(cur & BASE8BITS);
      }

      
      return decoded;
}


static int
getindexbychar(char c)
{
      const string base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefjhijklmnopqrstuvwxyz0123456789+/=";
      int i;
      for (i = 0; i < base.length(); i++)
            if (base[i] == c) return i;
      assert(i == base.length());
      return -1;
}