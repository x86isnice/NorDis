#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

inline double string2double(const std::string &str)
{
	double result;
	stringstream sstr(str);
	sstr >> result;
	return result;
}

int main()
{
   ifstream input;//file name
   input.open("/home/x86isnice/Match_Gen_PCL/testlog.txt");

   if (input.is_open())
   {
        std::vector<std::vector<double> > par_list;
		std::vector<double> P1;
		std::vector<double> P2;
		std::vector<double> SSE;
		std::vector<double> R_Square;
		vector<double> Ad_R_Square;
		vector<double> RMSE;

		P1.clear();P2.clear();SSE.clear();R_Square.clear();Ad_R_Square.clear();
		string str;
		while (!input.eof())
		{
		    std::getline(input,str);

			if ( str.find("p1",0) != string::npos && str.find(",",0) != string::npos )
			{
			  int begin = str.find_first_of("(");
			  int end =  str.find_first_of(")");
			  int middle = str.find_first_of(",");

			  double v1 = string2double(str.substr(begin + 1, middle - begin - 1));
			  double v2 = string2double(str.substr(middle + 2, end - middle - 2));
			  P1.push_back(static_cast<double>(v1 + v2)/2);
			}

			if ( str.find("p2") != string::npos && str.find(",") != string::npos )
			{
				int begin = str.find_first_of("(");
				int end =  str.find_first_of(")");
				int middle = str.find_first_of(",");

				double v1 = string2double(str.substr(begin + 1, middle - begin - 1));
				double v2 = string2double(str.substr(middle + 2, end - middle - 2));
				P2.push_back(static_cast<double>(v1 + v2)/2);
			}

			if ( str.find("sse") != string::npos )
			{
			   int begin = str.find_first_of(":");
			   double value = string2double(str.substr(begin + 2));
			   SSE.push_back(value);
			}
              
			if ( str.find("rsquare") != string::npos && str.find("adj") == string::npos)
			{
				int begin = str.find_first_of(":");
				double value = string2double(str.substr(begin + 2));
				R_Square.push_back(value);
			}

			if ( str.find("adjrsquare") != string::npos )
			{
				int begin = str.find_first_of(":");
				double value = string2double(str.substr(begin + 2));
				Ad_R_Square.push_back(value);
			}

			if ( str.find("rmse") != string::npos )
			{
				int begin = str.find_first_of(":");
				double value = string2double(str.substr(begin + 2));
				RMSE.push_back(value);
			}
		}
		input.close();
		par_list.push_back(P1);
		par_list.push_back(P2);
		par_list.push_back(SSE);
		par_list.push_back(R_Square);
		par_list.push_back(Ad_R_Square);
		par_list.push_back(RMSE);
		/*
		for (int i = 0; i < par_list[0].size(); i++)
		{
			for (int j = 0; j < par_list.size(); j++)
			{
				std::cout << par_list[j][i] << " "<<endl;
			}
			std::cout << endl;
		}
		*/
		std::ofstream out("/home/x86isnice/Match_Gen_PCL/result.txt");
		for (int j = 0; j < par_list.size(); j++)
		{
		    out <<char(j + 65)<<"=[";
			for (int i = 1; i < par_list[j].size()-1; i++)
			{
			  out << par_list[j][i] <<",";
			}
			out << par_list[j][par_list[j].size()-1]<<"];"<<endl<<endl;
		}

		out.close();
   }
   else
   {
       std::cout << " file  open error!" << std::endl;
	 return -1;
   }

   
 return 0;
}
