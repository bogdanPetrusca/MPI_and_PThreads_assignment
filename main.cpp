#include "mpi.h"
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <vector>
using namespace std;

#define MASTER 0
#define nr_workers 4
#define P 4
 
string in;

string read_buffer(ifstream &f, int &nr) {
	string buffer = "", line;
	while(getline(f, line)) {
		if(line[0] == 0)
			break;
		else {
			buffer.append(line + "\n");
			nr++;
		}
	}
	return buffer;
}

void add_elem(vector<string> &par, int nr) {
	while(par.size() <= nr)
		par.push_back("");
}



vector<string> paragraphs;
int cont_h = 0, cont_c = 0, cont_f = 0, cont_sf = 0;
void *func(void *arg) {
	int thread_id = *(int *)arg;
	if (thread_id == 1) {
		bool eof = false;
		ifstream fin(in);
		string line;
		while(getline(fin, line)) {
			if(!line.compare("horror")) {
				MPI_Send(&eof, 1, MPI_C_BOOL, 1, 1, MPI_COMM_WORLD);
				int nr_lines;
				string buffer = read_buffer(fin, nr_lines);
				
				paragraphs.push_back("");

				MPI_Send(&nr_lines, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
				int size = buffer.size();
				MPI_Send(&size, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

				char vec[size + 1] = {0};

				strcpy(vec, buffer.c_str());
				MPI_Send(vec, size + 1, MPI_CHAR, 1, cont_h, MPI_COMM_WORLD);
				cont_h++;

				MPI_Status status;
				bool is_sent;
				MPI_Recv(&is_sent, 1, MPI_C_BOOL, 1, 0, MPI_COMM_WORLD, &status);
				
				if (is_sent) {
					int size;
					MPI_Recv(&size, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

					char res[size + 1];
					MPI_Recv(res, size + 1, MPI_CHAR, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					string result = string(res);

					while(paragraphs.size() <= status.MPI_TAG)
						paragraphs.push_back("");

					string type = "horror\n";
					
					string aux = paragraphs.at(status.MPI_TAG);
					aux.append(type);
					aux.append(result);
					aux.append("\n");

					
					paragraphs.at(status.MPI_TAG) = aux;


				}

				nr_lines = 0;
			} else if(!line.compare("comedy") || !line.compare("fantasy") || !line.compare("science-fiction")) {
				cont_h++;
			}

		}
		eof = true;

		MPI_Send(&eof, 1, MPI_C_BOOL, 1, 1, MPI_COMM_WORLD);
		fin.close();
	}
	if (thread_id == 2) {
		ifstream fin(in);
		string line;
		bool eof = false;
		while(getline(fin, line)) {
			if(!line.compare("comedy")) {
				MPI_Send(&eof, 1, MPI_C_BOOL, 2, 1, MPI_COMM_WORLD);
				int nr_lines;
				string buffer = read_buffer(fin, nr_lines);
				
				paragraphs.push_back("");

				MPI_Send(&nr_lines, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
				int size = buffer.size(), size_aux = buffer.size();
				MPI_Send(&size, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

				char vec[size_aux + 1] = {0};

				strcpy(vec, buffer.c_str());
				MPI_Send(vec, size + 1, MPI_CHAR, 2, cont_c, MPI_COMM_WORLD);
				cont_c++;

				MPI_Status status;
				bool is_sent;
				MPI_Recv(&is_sent, 1, MPI_C_BOOL, 2, 0, MPI_COMM_WORLD, &status);
				
				if (is_sent) {
					int size;
					MPI_Recv(&size, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);

					char res[size + 1];
					MPI_Recv(res, size + 1, MPI_CHAR, 2, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					string result = string(res);


					while(paragraphs.size() <= status.MPI_TAG)
						paragraphs.push_back("");

					string type = "comedy\n";
					string aux = paragraphs.at(status.MPI_TAG);
					aux.append(type);
					aux.append(result);
					aux.append("\n");

					
					paragraphs.at(status.MPI_TAG) = aux;
				} 


				nr_lines = 0;
			}	else if(!line.compare("horror") || !line.compare("fantasy") || !line.compare("science-fiction")) {
					cont_c++;
			}

		}

		eof = true;

		MPI_Send(&eof, 1, MPI_C_BOOL, 2, 1, MPI_COMM_WORLD);
		fin.close();
	}
	if (thread_id == 3) {
		ifstream fin(in);
		string line;
		bool eof = false;
		while(getline(fin, line)) {
			if(!line.compare("fantasy")) {
				MPI_Send(&eof, 1, MPI_C_BOOL, 3, 1, MPI_COMM_WORLD);
				int nr_lines;
				string buffer = read_buffer(fin, nr_lines);
				
				paragraphs.push_back("");

				MPI_Send(&nr_lines, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
				int size = buffer.size(), size_aux = buffer.size();
				MPI_Send(&size, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);

				char vec[size_aux + 1] = {0};

				strcpy(vec, buffer.c_str());
				MPI_Send(vec, size + 1, MPI_CHAR, 3, cont_f, MPI_COMM_WORLD);
				cont_f++;

				MPI_Status status;
				bool is_sent;
				MPI_Recv(&is_sent, 1, MPI_C_BOOL, 3, 0, MPI_COMM_WORLD, &status);
				
				if (is_sent) {
					int size;
					MPI_Recv(&size, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, &status);

					char res[size + 1];
					MPI_Recv(res, size + 1, MPI_CHAR, 3, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					string result = string(res);


					while(paragraphs.size() <= status.MPI_TAG)
						paragraphs.push_back("");

					string type = "fantasy\n";
					string aux = paragraphs.at(status.MPI_TAG);
					aux.append(type);
					aux.append(result);
					aux.append("\n");

					
					paragraphs.at(status.MPI_TAG) = aux;
				} 


				nr_lines = 0;
			} else if(!line.compare("comedy") || !line.compare("horror") || !line.compare("science-fiction")) {
					cont_f++;
			}

		}

		eof = true;
		MPI_Send(&eof, 1, MPI_C_BOOL, 3, 1, MPI_COMM_WORLD);
		fin.close();
	}
	if (thread_id == 4) {
		ifstream fin(in);
		string line;
		bool eof = false;
		while(getline(fin, line)) {
			if(!line.compare("science-fiction")) {
				MPI_Send(&eof, 1, MPI_C_BOOL, 4, 1, MPI_COMM_WORLD);
				int nr_lines;
				string buffer = read_buffer(fin, nr_lines);
				
				paragraphs.push_back("");

				MPI_Send(&nr_lines, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
				int size = buffer.size(), size_aux = buffer.size();
				MPI_Send(&size, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);

				char vec[size_aux + 1] = {0};

				strcpy(vec, buffer.c_str());
				MPI_Send(vec, size + 1, MPI_CHAR, 4, cont_sf, MPI_COMM_WORLD);
				cont_sf++;

				MPI_Status status;
				bool is_sent;
				MPI_Recv(&is_sent, 1, MPI_C_BOOL, 4, 0, MPI_COMM_WORLD, &status);
				
				if (is_sent) {
					int size;
					MPI_Recv(&size, 1, MPI_INT, 4, 0, MPI_COMM_WORLD, &status);

					char res[size + 1];
					MPI_Recv(res, size + 1, MPI_CHAR, 4, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					string result = string(res);


					while(paragraphs.size() <= status.MPI_TAG)
						paragraphs.push_back("");

					string type = "science-fiction\n";
					string aux = paragraphs.at(status.MPI_TAG);
					aux.append(type);
					aux.append(result);
					aux.append("\n");

					
					paragraphs.at(status.MPI_TAG) = aux;

				}


				nr_lines = 0;
			} else if(!line.compare("comedy") || !line.compare("fantasy") || !line.compare("horror")) {
					cont_sf++;
			}
		}

		eof = true;
		MPI_Send(&eof, 1, MPI_C_BOOL, 4, 1, MPI_COMM_WORLD);
		fin.close();
	}
	pthread_exit(NULL);
}



bool isVowel(char ch) { 
    ch = toupper(ch); 
    return (ch == 'A' || ch == 'E'
            || ch == 'I' || ch == 'O'
            || ch == 'U'); 
} 

string horror_transform(string str) {
	int t = str.length(); 
  
    string res = ""; 
  
    for (int i = 0; i < t; i++) { 
        res += str[i]; 
		if (isalpha(str[i]) && !isVowel(str[i])) { 
            res += tolower(str[i]); 
        } 
    } 

	res.push_back(' ');


    return res; 
}

string comedy_transform(string str) {
	int t = str.size();

	string res = "";
	
	int poz = 0;
	for(int i = 0; i < t; i++) {
		
		if(str[i] == ' ' || str[i] == '\n') {
			poz = 0;
			res += str[i];
		} else {
			if(poz % 2 != 0)
				res += toupper(str[i]);
			else
				res += str[i];
			poz++;
		}
	}
	res.push_back(' ');


	return res;
}

void reverse(string& str) {
	int n = str.length();

	for(int i = 0; i < n / 2; i++)
		swap(str[i], str[n - i - 1]);
}

string fantasy_transform(string str) {
	int t = str.size();

	string res = "";

	for(int i = 0; i < t; i++) {
		if(isalpha(str[i]) && (i == 0 || (i != 0 && (str[i - 1] == ' ' || str[i - 1] == '\n'))))
			res += toupper(str[i]);
		else
			res += str[i];
	}
	res.push_back(' ');


	return res;
}

bool isValid(char c) {
	return (c >= 0 && c <= 9) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

string sf_transform(string str) {
	
	string res = "";

	int t = str.size();
	int cont = 0;
	string word = "";

	for(int i = 0; i < t; i++) {
		
		if(str[i] == ' ') {
			cont++;
			if(cont == 7) {
				reverse(word); 
				cont = 0;
			}
			res += word;
			res += " ";
			word = "";
		} else {
			word += str[i];
		}

	}

	if(cont == 6) reverse(word);
	res += word;

	res.push_back(' ');

	return res;

}



int get_nr_threads(int nr_lines) {
	int nr_of_threads = 0;
	if(nr_lines == 0)
		return 0;
	if (nr_lines <= 20)
		nr_of_threads = 2;
	else
		nr_of_threads = nr_lines / 20 + 2;
	return nr_of_threads;
}


std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

struct params {
	int thread_id;
	int nr_threads;
	int nr_lines;
	int rank;
	int start;
	vector<string> v;
	string *ret_str;
};


void *worker_func(void *arg) {
	struct params par = *(struct params *)arg;
	int len;
	int next_line = par.nr_lines;
	int aux = 60;

	int end = min(par.nr_lines, par.start + 20);


	for(int i = par.start; i < end; i++) {
		
 		if(par.rank == 1){
			string aux = horror_transform(par.v[i]);
			par.ret_str->append(aux + "\n");
		}
		if(par.rank == 2) {
			string aux = comedy_transform(par.v[i]);	
			par.ret_str->append(aux + "\n");
		}
		if(par.rank == 3) {
			string aux = fantasy_transform(par.v[i]);	
			par.ret_str->append(aux + "\n");
		}
		if(par.rank == 4) {
			string aux = sf_transform(par.v[i]);	
			par.ret_str->append(aux + "\n");
		}
	}

	pthread_exit(NULL);
}



void *recv_func(void *arg) {
	bool is_eof = false;
	int rank = *(int *)arg;

	while(1) {
		MPI_Status status, status_buf;
		MPI_Recv(&is_eof, 1, MPI_C_BOOL, 0, 1, MPI_COMM_WORLD, &status);
		if(is_eof == true)
			break;

		string buffer = "";
		int nr_lines;
		MPI_Recv(&nr_lines, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		int nr_threads = get_nr_threads(nr_lines);
		nr_threads = min(nr_threads, P);

		int len;
		MPI_Recv(&len, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		char *vec = new char[len + 1];
		MPI_Recv(vec, len + 1, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status_buf);
		buffer = string(vec);


		vector<string> v = split_string(buffer, "\n");

		pthread_t threads[nr_threads - 1];

		void *p_status;

		struct params par[nr_threads - 1];

		int cont = 0, nr_threads_aux = nr_threads;

		string result = "";

		while(cont < nr_lines) {
		    for (int i = 0; i < nr_threads - 1; i++) {
				par[i].thread_id = i;
				par[i].nr_threads = nr_threads - 1;
				par[i].rank = rank;
				par[i].nr_lines = nr_lines;
				par[i].start = cont;
				par[i].v = v;
				par[i].ret_str = new string("");


				cont = min(nr_lines, cont + 20);
				int r = pthread_create(&threads[i], NULL, worker_func, &par[i]);

				if (r) {
					printf("Eroare la crearea thread-ului %d in WORKER\n", i);
					exit(-1);
				}
			}
			
			for (int i = 0; i < nr_threads - 1; i++) {
				int r = pthread_join(threads[i], &p_status);

				if (r) {
					printf("Eroare la asteptarea thread-ului %d\n", i);
					exit(-1);
				}
				int size = par[i].ret_str->size();

				result.append(*(par[i].ret_str));
			}
			
		}
		
		int size = result.size();
		bool to_send = true;
		MPI_Send(&to_send, 1, MPI_C_BOOL, 0, 0, MPI_COMM_WORLD);


		MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

		char res[size + 1];
		strcpy(res, result.c_str());
		MPI_Send(res, size + 1, MPI_CHAR, 0, status_buf.MPI_TAG, MPI_COMM_WORLD);


			
	}
	pthread_exit(NULL);
}

int main(int argc, char * argv[]) {

	in = argv[1];

	
	int procs, rank;
	int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == MASTER) {
		
			
		
    	pthread_t threads[nr_workers];
    	
    	void *status;
    	int arguments[nr_workers];
	    for (int i = 1; i <= nr_workers; i++) {
			arguments[i] = i;
			int r = pthread_create(&threads[i], NULL, func, &arguments[i]);

			if (r) {
				printf("Eroare la crearea thread-ului %d in MASTER\n", i);
				exit(-1);
			}
		}

		for (int i = 1; i <= nr_workers; i++) {
			int r = pthread_join(threads[i], &status);

			if (r) {
				printf("Eroare la asteptarea thread-ului %d\n", i);
				exit(-1);
			}
		}
		//cout << in << endl;
		string out = "";

		for(int i = 2; i < in.size(); i++) {
			out.push_back(in[i]);
			if(in[i] == '.')
				break;
		}
		out.append("out");
		//cout << "out: "<<out << endl;

		ofstream fout(out);
		for(int i = 0; i < paragraphs.size(); i++)
			fout << paragraphs[i];

		fout.close();

    } else {
    		
    	pthread_t thread;
    	void *status;
    	int r = pthread_create(&thread, NULL, recv_func, &rank);

		if (r) {
			printf("Eroare la crearea thread-ului 0 in WORKER\n");
			exit(-1);
		}

		r = pthread_join(thread, &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului 0\n");
			exit(-1);
		}
    	
    }
    MPI_Finalize();
	
	return 0;
}