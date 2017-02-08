#ifndef CREATELIB_H
#define CREATELIB_H
class myclass
{
	public:
		myclass()
		{
			x = 0;
			y = 0;
		}
		~myclass(){}
		void show();
	private:
		int x;
		int y;
};
#endif