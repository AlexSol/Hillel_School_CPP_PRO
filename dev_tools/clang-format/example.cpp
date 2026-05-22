#include <iostream>
#include <vector>

int   sum( const std::vector<int>& values ){
int result=0;
for(auto value:values){result+=value;}
return result;
}

int main(){std::vector<int> values={1,2,3,4,5};if(sum(values)>10){std::cout<<"sum is greater than 10"<<std::endl;}else{std::cout<<"sum is 10 or less"<<std::endl;}return 0;}
