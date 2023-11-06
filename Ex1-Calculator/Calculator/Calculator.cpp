#include <iostream>
#include <stdexcept>

using namespace std;

int calculatorSwitch( char calcxOperator , float numx , float numy ) 
{
    switch (calcxOperator)
    {
    case '+':
        return numx + numy;
        break;
    case '-':
        return numx - numy;
        break;
    case '*':
        if (numx==0 && numy==0)
        {
            cout << "\ntanimsiz davranis algilandi\n";
                return 0;
        }
        return numx * numy;
        break;
    case '/':
        if (numy == 0)
        {
            cout << "\ntanimsiz davranis algilandi\n";
                return 0;
        }
        return numx / numy;
        break;
    }

}

bool startcalculator(char calcOperator)
{
    float numberx, numbery;
    if (calcOperator == 'q')
    {
        return  false;
    }
    else if (calcOperator == '+' || calcOperator == '-' || calcOperator == '*' || calcOperator == '/')
    {
        cout << "1. sayiyi girin \n";
        cin >> numberx;
        cout << "2. sayiyi girin \n";
        cin >> numbery;
        cout << "\n";

        if ( 
            ( !(isnan<float>(numberx)) && !(isnan<float>(numbery)) )
            //&&
            //(  (isfinite<float>(numberx)) && (isfinite<float>(numbery)) )
            )
        {
            cout << "\n" << " sonuc :" << calculatorSwitch(calcOperator, numberx, numbery) << "\n";
        }
        else {
            cout << "Sayilar hatali girildi .\n Basa donuluyor . . \n";
             }
    }
    else
    {
        cout << "Hatali islem belirttiniz. \n Basa donuluyor . . \n";
    }
    return true;

}


int main()
{
    bool iscalcopen = true ;
    char calcOperator; 

    while (iscalcopen)
    {
        cout << "Bir islem belirtiniz \n + , - , * , /\n kapatmak icin q ya basin\n";
        cin >> calcOperator;
        iscalcopen = startcalculator(calcOperator); 
    }
}
