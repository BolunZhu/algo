#include <cstdlib>
int main()
{
while (1)
{
system("./1-3input > input.txt");
system("./1-3std < input.txt > std.txt");
system("./a.out  < input.txt  > out.txt");
int f = system("diff out.txt std.txt");

if(f)
{
    break;
}
system("echo ok");
}
return 0;
} 