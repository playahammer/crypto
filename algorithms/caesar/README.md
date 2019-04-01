# Caesar

## Preface
Caesar is very classical encryption algorithm, which was created in about 100 B.C by Julius Caesar, the acient Roman leader. 
It has been used in war to delivery the war plans or commands secretly. The rule of caesar is replacing the word by add ```k```
cursor position word. if the ```k = 3```, the relationship between plaintext and ciphertext after replaced as follows.

```bash
(A B C D E F G H I J K L M N O P Q R S T U V W X Y Z)
(D E F G H I J K L M N O P Q R S T U V W X Y Z A B C)
```
As we can see, in caesar, the argument ```k``` is private key. if the 26 words correspond to 0~25 integers, such as the 1 corresponds to a,
2 corresponds to b, ... 25 corresponds to y, 0 corresponds to z. In fact the caesar encryption operation is a congruence equation.
```bash
c =  m + k mod 26
```
In above equation, the ```m``` is the plaintext corresponded to the integer. The ```c``` is the ciphertext corresponded to the integer. The 
private key ```k``` is a confirm random integer ranging from 1 to 25;

## Codes

This encryption algorithm is implemented by C++ using Qt supporting the GUI. The main functions are ```QString encrypt(QString)``` and  ```QString decrypt(QString)```,
which need the plaintext or ciphertext and return the cipertext or plaintext respectively. But before this, we show initialize the ```Caesar``` class pointer
with private key constructor. More details please see the ```caesar.cpp``` and ```caesar.h```.
