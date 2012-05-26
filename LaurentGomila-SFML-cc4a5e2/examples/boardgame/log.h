#ifndef LOG
#define LOG

class Logs
{
	public:
	FILE * pfile;

	void open(char * file);
	void logit(char * in);
	void close();
	static Logs * Instance();
	private:
	Logs(){};
	Logs(Logs const&){};
	Logs& operator=(Logs const&){};
	static Logs * p_Instance;


};
#endif
