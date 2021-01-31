#include <iostream>
using namespace std;

int main()
{
    int A[10];
    for(int i=0;i<10;i++){
        cin>>A[i];
    }

    for(int i=0;i<10;i++){
        bool flag = true;

        int n = A[i];
        if(n == 1){
            continue;
        }
        for(int j=3;j <= n/2;j++){
            if(n % j == 0){
                flag = false;
                break;
            }
        }
        if(flag == true)
        cout<<n<<endl;
    }
    
    return 0;
}