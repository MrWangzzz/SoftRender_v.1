#include "ObjFileReader.h"
#include <iostream>


void StringSplit(string s, char splitchar, vector<string>& vec)
{
	if (vec.size() > 0)//��֤vec�ǿյ�  
		vec.clear();
	int length = s.length();
	int start = 0;
	for (int i = 0; i < length; i++)
	{
		if (s[i] == splitchar && i == 0)//��һ���������ָ��  
		{
			start += 1;
		}
		else if (s[i] == splitchar)
		{
			vec.push_back(s.substr(start, i - start));
			start = i + 1;
		}
		else if (i == length - 1)//����β��  
		{
			vec.push_back(s.substr(start, i + 1 - start));
		}
	}
}

void ReadObjFile(string path, Mesh* obj)
{
	ifstream in(path);
	string txt = "";
	if (in) // �и��ļ�  
	{
		while (getline(in, txt)) // line�в�����ÿ�еĻ��з�  
		{
			//��������
			if (txt[0] == 'v' && txt[1] == ' ')
			{
				vector<string> num;
				txt.erase(0, 2);
				StringSplit(txt, ' ', num);
				Vector3<float> pos;
				pos = Vector3<float>((float)atof(num[0].c_str()), (float)atof(num[1].c_str()), (float)atof(num[2].c_str()));
				//pos.Print();
				obj->positionBuffer.push_back(pos);
			}
			//���㷨��
			else if (txt[0] == 'v' && txt[1] == 'n')
			{
				vector<string> num;
				txt.erase(0, 3);
				StringSplit(txt, ' ', num);
				Vector3<float> n = Vector3<float>((float)atof(num[0].c_str()), (float)atof(num[1].c_str()), (float)atof(num[2].c_str()), 0.0);
				//n.Print();
				obj->normalBuffer.push_back(n);
			}
			//uv
			else if (txt[0] == 'v' && txt[1] == 't')
			{
				vector<string> num;
				txt.erase(0, 3);
				StringSplit(txt, ' ', num);
				//Vector2((float)atof(num[0].c_str()), (float)atof(num[1].c_str()));
				obj->uvBuffer.push_back(Vector2((float)atof(num[0].c_str()), (float)atof(num[1].c_str())));
				//cout << (float)atof(num[0].c_str()) << " " << (float)atof(num[1].c_str()) << endl;

			}
			//�������
			//��"f 7/13/21"��ʱ����������ж�����ͼ����uv��ͷ��ߵ������ţ������ŷֱ�����б��(/)������ 
			else if (txt[0] == 'f' && txt[1] == ' ')
			{
				vector<string> num;
				txt.erase(0, 2);
				StringSplit(txt, ' ', num);
				//vector<string> index;
				for (int i = 0; i < num.size(); i++)
				{
					vector<string> threeIndex;
					StringSplit(num[i], '/', threeIndex);
					Vector3<int> indexes = { atoi(threeIndex[0].c_str()), atoi(threeIndex[1].c_str()), atoi(threeIndex[2].c_str()) };
					//indexes.Print();
					obj->indexBuffer.push_back(indexes);
				}
			}
		}
	}
	else // û�и��ļ�  
	{
		cout << "no file" << endl;
	}
}
