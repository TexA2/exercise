#include <iostream>
#include <string>
#include <cmath>

using namespace std; 

int compute(int a, int m, int n)
{
    int r;
    int y = 1;
 
    while (m > 0)
    {
        r = m % 2;

        if (r == 1)
		{
            y = (y*a) % n;
        }
        a = a*a % n;
        m = m / 2;
    }
 
    return y;
} 


int crypt(int p, int g, int x, int msg, int &a, int&b)
{
	int sol;
		
	int y = compute(g,x,p);  // 3-й открытый ключ
	cout << "open key p: "  << p << " g: " << g << " y: " << y << endl;
	
	
	int m = msg;    		// шифруемый текст

		
	// выбираем случайное число k
	srand(time(NULL));
	int k=rand()%(p-2)+1; // 1 < k < (p-1)
	
	//вычисляем число a
	a = compute(g,k,p);	
	
	//вычисляем число b
	b = compute(pow(y,k)*m,1,p);

	sol = b;
				
	return sol;
}

 
int mul(int a, int b, int n){// a*b mod n
    int sum=0;
     
    for(int i=0;i<b;i++){
        sum+=a;
         
        if(sum>=n){
            sum-=n;
        }
    }
 
    return sum;
}


int main(){

// p больше простое число
// g первообразый корень числа p

/*
https://forum.sources.ru/index.php?showtopic=281417

в комментарии обьяснили что такое первообразный корень
*/

	int p = 11, g =2; // общий элементы
	int a; 
	int b;

	
// Этап Шифрования
// Пользователь B хочет отправить сообщение пользователю А

	int x = 8; 									// Закрытый ключ
	
	cout << "Private key: " << x << endl;
	
	int msg = 5; 								//	Отправляемое сообщение	
	cout << "Original text: " << msg << endl;
	
	int cr_msg = crypt(p,g,x,msg,a,b);
	cout << "Cripted text: " << cr_msg << endl;
	
// Расшифровка
	// Пользователь А вычесляет зашифрованное слово;
	cout << endl;
	
	int sol = mul(b,compute(a,p - 1 - x , p),p);
	cout <<"Solution: " <<sol << endl;

	return 0;
}
