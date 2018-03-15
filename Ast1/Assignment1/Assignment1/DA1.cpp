#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	
	uint counter = 0x0222;
	int div5 = 0;
	int not5 = 0;
	uint8_t high;
	uint8_t low;
	uint8_t ans;

	for(int i = 0; i < 300; i++)
	{
		high = counter / 0x100;
		low = counter % 0x100;
		//cout<< high<<" "<<low<<endl;
		//cout<<high + low <<endl;
		ans = high + low;
		if(((high + low) % 5) == 0)
		{
			//cout<<high + low <<endl;
			div5 = div5 + ans;
		}

		else
		{
			not5 = not5 + ans;
		}
		counter++;
	}

	cout <<"Disvisable by 5: "<<div5<<endl<<"Not Disvisable by 5: "<<not5<<endl;

	return 0;
}