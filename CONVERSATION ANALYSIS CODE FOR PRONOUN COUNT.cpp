#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int main()
{
	ifstream in;
	string readLine,word,temp_word;
	string words[999];
	int pos_start=-1,pos_end=-1,token_flag=-1,length=0,i=0,j=0,k=0,l=0,m=0;
	int word_count=0,word_exist=0,word_pos=-1,pro_pos1=-1,pro_pos2=-1,token_id_3_pos=-1;
	int temp_count =0,pos_cd_flag=-1,ner_time_flag=-1,word_flag=0,sentence_flag=-1;
	int pro_count[30];
	
	//open file for reading
	in.open("input.txt");
	
	//check wether read is successful or not
	if(in.fail())
	{
		cout<<"Sorry, I Cant read the file or file missing :(\n\n";
		exit(1);
	}
	else
	{
		cout<<"Yeah, File is read successfully :)\n\nNames Found in the File:\n";
		while(!in.eof())
		{
			getline(in,readLine);
			//cout<<readLine<<endl;
			//length = readLine.length();
			token_flag = readLine.find("<token id=\"1\">");
			if(token_flag>=0)
			{
				//toekn id is 1 so check for word tag
				getline(in,readLine);
				pos_start = readLine.find("<word>");
				if(pos_start>=0)
				{
					pos_end = readLine.find("</word>");
					pos_start+=6; //beacuse of <word> which is 6 
					temp_word = readLine.substr (pos_start,pos_end-pos_start); //temp_word beacuse its not yet confirmed as a word
					temp_count=0;
					//check the time flag
					do{
						getline(in,readLine);
						token_id_3_pos = readLine.find("<token id=\"3\">");
						pro_pos1=readLine.find("<POS>PRP</POS>");
						pro_pos2=readLine.find("<POS>PRP$</POS>");
						sentence_flag=readLine.find("</sentence>");
						if(pro_pos1>=0 || pro_pos2>=0)
								temp_count++;
						if(sentence_flag>0)
						{
							token_id_3_pos=-1;
							break;
							//goto a1;
						}
					}while(token_id_3_pos<0);
					//a1:
					if(token_id_3_pos>0)
					{
						getline(in,readLine);getline(in,readLine);getline(in,readLine);getline(in,readLine);getline(in,readLine);
						//check wether it is a pronoun or not
						pro_pos1=readLine.find("<POS>PRP</POS>");
						pro_pos2=readLine.find("<POS>PRP$</POS>");
						if(pro_pos1>=0 || pro_pos2>=0)
						{
								temp_count++;
						}
						pos_cd_flag=readLine.find("<POS>CD</POS>");
						if(pos_cd_flag>0)
						{
							getline(in,readLine);
							ner_time_flag=readLine.find("<NER>TIME</NER>");
							if(ner_time_flag>0)
							{
								//yes then it is a word
								//check weather name already exists !!
								word=temp_word;
								for(m=0;m<word_count;m++)
								{
									word_exist=0;
									if(word.compare(words[m])==0)
									{
										word_exist=1;
										word_pos=m;
										break;
									}
								}
								if(word_exist==0)
								{
									words[k++]=word;
									cout<<"Name "<<k<<" = "<<words[k-1]<<endl; 
									word_count++;
									//pro_count[k-1]+=temp_count;
								}
								//else
									//pro_count[m]+=temp_count;
							}
						}
						for(m=0;m<word_count;m++)
						{
							if(word.compare(words[m])==0)
							{
								word_pos=m;
								break;
							}
						}
						pro_count[word_pos]+=temp_count;
					}
					else
					{
						//word already exists so find its postion and update temp_count into it.
						for(m=0;m<word_count;m++)
						{
							if(word.compare(words[m])==0)
							{
								word_pos=m;
								break;
							}
						}
						pro_count[word_pos]+=temp_count;
					}
				}
			}//end of (if toekn id =1)
			else
			{
				//checking pronouns
				pro_pos1=readLine.find("<POS>PRP</POS>");
				pro_pos2=readLine.find("<POS>PRP$</POS>");
				if(pro_pos1>=0 || pro_pos2>=0)
				{
					
					/*for(m=0;m<word_count;m++)
						{
							if(word.compare(words[m])==0)
							{
								word_pos=m;
								break;
							}
						}
						pro_count[word_pos]+=1;
					*/

					if(word_exist==1)
						pro_count[m]+=1;
					else 
						pro_count[k]+=1;
				}
			}
		}//end while
	}//end else for file read
	// close the file after reading
	in.close();
	cout<<"\nPronoun Count:\n";
	for(i=0;i<word_count;i++)
		cout<<words[i]<<" - "<<pro_count[i]<<endl;
	return 0;
}
