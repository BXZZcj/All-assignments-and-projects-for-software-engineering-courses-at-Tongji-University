#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
vector<char> vt;//�ս����������
vector<char> vn;//���ս����������
string ST="#";//����ջ,Ԥ��ѹ��#
string inputs;//�û�����ķ��Ŵ�
string subinput;//ʣ���Ӵ�
int input_flag = 1;//�����Ӵ��Ƿ�ʱ����Ϊ0
vector<vector<string>> firstvt;//firstvt�������顣���磬��firstvt[i][0]="E".firstvt[i][1]="abc",��ʾfirstvt(E)={a,b,c}
vector<vector<string>> lastvt;//lastvt�������飬ͬ��
vector<vector<char>> table;//����������ȹ�ϵ��,table[i][j]��ʾvt[i]��vt[j]�Ĺ�ϵ
//�û����ķ�һ��һ�����뵽ͬĿ¼�µ�suanfuyouxianwenfa.txt�ļ���
void input_file()
{
	string a;
	ofstream ofs;
	ofs.open("suanfuyouxianwenfa.txt", ios::out);
	cout << "�������ķ���(��������������һ��ֻ����#)" << endl;
	while (1) {
		cin >> a;
		if (a == "#")
		{
			break;
		}
		ofs << a << endl;
	}


	ofs.close();
}
//��ȡͬĿ¼�µ�suanfuyouxianwenfa.txt�ļ�������ķ�������ֺõ��ķ�д�뵽split.txt�ļ���
//����ֵΪ��ʼ����
void split()
{

	string a;//���ڶ�ȡÿ���ַ���
	string b;//���ڴ�Ų�ֺ���ַ���
	int c;//��ʾ|���ֵ�λ��
	ifstream ifs;
	ofstream ofs;
	ifs.open("suanfuyouxianwenfa.txt", ios::in);
	ofs.open("split.txt", ios::out);
	while (getline(ifs, a))
	{
		while (1)
		{
			c = a.find("|");
			if (c == -1)
			{
				ofs << a << endl;
				break;
			}
			else {
				b = a.substr(0, c);
				ofs << b << endl;;
				a.erase(3, c - 3+1);
			}
		}
	}

	ifs.close();
	ofs.close();


}
//�ж��������Ƿ�洢ĳ�����ս��,�з����������޷���-1
int find_bigchar(vector<vector<string>> S, char a)
{
	string c;
	c = a;
	for (int i = 0; i < S.size(); i++)
	{
		if (S[i][0] == c)
		{
			return i;
		}
	}
	return -1;
}
//�ж��������Ƿ�洢ĳ���ս��,�з���1���޷���0
int find_smallchar(vector<vector<string>>  S, char a,int indx)
{
	
	for (int i = 0; i < S[indx][1].size(); i++)
	{
		if (S[indx][1][i]== a)
		{
			return 1;
		}
	}
	return 0;
}
//��ȡ�ķ��еķ��ս���洢��vn�У��ս���洢��vt��
void read_char()
{
	string a;
	ifstream ifs;
	ifs.open("split.txt", ios::in);
	while (getline(ifs, a))
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] >= 'A' && a[i] <= 'Z')
			{
				if (find(vn.begin(), vn.end(),a[i])==vn.end() )//��û���ظ���
				{
					vn.push_back(a[i]);                      
				}
			}
			else if (i!=1 && i!=2&&a[i]!=' ')
			{
				if (find(vt.begin(), vt.end(), a[i]) == vt.end())
				{
					vt.push_back(a[i]);
				}
			}
		}
	}
	//����̨�������ջ
	cout << "���ķ��ķ��ս��Ϊ��";
	for (int i = 0; i < vn.size(); i++) {
		cout << vn[i] << "  ";
	}
	cout << endl;
	cout << "���ķ����ս��Ϊ��";
	for (int i = 0; i < vt.size(); i++) {
		cout << vt[i] << "  ";
	}
	cout << endl;
	ifs.close();
}
//���ս�������в���ĳ���ս�������ҵ�������index�����򷵻�-1
int find_vt(vector<char> vt1, char a)
{
	for (int i = 0; i < vt1.size(); i++)
	{
		if (vt1[i] == a)
		{
			return i;
		}
	}
	return -1;
}
//�Ƚ������ַ������ȼ���ϵ�����رȽ��ַ�
char com_twochars(char a, char b)
{
	return table[find_vt(vt, a)][find_vt(vt, b)];
}
//�����ƽ�
void movein()
{
	cout << "�ƽ�" << "   ";
	ST.insert(ST.begin(), inputs[0]);
	inputs.erase(inputs.begin());
	cout << ST << "         " << inputs << endl;
}
//������Լ
void reduce(int k)
{
	int k1 = k;//�ݴ�
	k++;
	int flag = 0;//�Ƿ��ҵ����ʵĹ�Լʽ
	cout << "��Լ" << "   ";
	string a;
	ifstream ifs;
	while (1)
	{
		if ((ST[k] <= 'Z' && ST[k] >= 'A') )
		{
			k = k + 1;
		}
		else if (com_twochars(ST[k1], ST[k]) == '=')
		{
			k1 = k;
			k = k + 1;
		}
		else if (com_twochars(ST[k1], ST[k]) == '>')
		{
			//�ҵ����ʵĹ�Լ��ѡʽ
			
			ifs.open("split.txt", ios::in);
			while (getline(ifs, a))
			{
				if ((a.size() - 3) ==k )
				{
					int i = 0;
					for (; i < k ; i++)
					{
						if (a[i + 3] != ST[k - i-1]&& !(ST[k-i-1] <= 'Z' && ST[k-i-1] >= 'A'&& a[i + 3] <= 'Z' && a[i + 3] >= 'A'))
						{
							break;
						}
					}
					if (i == k )
					{
						flag = 1;
						ST.erase(ST.begin(), ST.begin()+k);
						ST.insert(ST.begin(), a[0]);
						break;
					}
				}
			}
			ifs.close();
			if (flag == 0)
			{
				cout << "δ�ҵ����ʵĹ�Լʽ,ERROR" << endl;
				input_flag = 0;
				return;
			}
			break;
		}
		else {
			cout << "��Լʱ������վ�ڱȽϳ���ERROR" << endl;
			input_flag = 0;
			return;
		}
	}
	
	cout << ST << "         " << inputs << endl;
}
//������ʽ�Ҳ��Ƿ�������������ķ��ս�������з���1.���򷵻�0
int check_two_bigchar()
{
	int i = 3;
	string a;
	ifstream ifs;
	ifs.open("split.txt", ios::in);
	while (getline(ifs, a))
	{
		for (; i< a.size() - 1; i++)
		{
			if (a[i] <= 'Z' && a[i] >= 'A' && a[i + 1] <= 'Z' && a[i + 1] >= 'A')
			{
				return 1;
			}
			
		}
		
	}
	ifs.close();
	return 0;
}
//����ÿһ�����ս����FirstVT���ϣ�����ӡ����
void Get_firstvt()                    
{
	//ɨ���ķ�
	int index;
	int firstsize = 0;
	int flag = 0;//�жϼ����Ƿ��ٱ仯
	string c;
	vector<string> fv;
	string a;//���ж��ļ�
	ifstream ifs;
	ifs.open("split.txt", ios::in);
	while (getline(ifs, a))
	{
		if (find_bigchar(firstvt, a[0])==-1)//û�д˷��ս��
		{
			for (int i = 3; i < a.size(); i++)//�ҵ���һ���ս��
			{
				if (!(a[i] <= 'Z' && a[i] >= 'A')&&a[i]!=' ')
				{
					c = a[0];
					fv.push_back(c);
					c = a[i];
					fv.push_back(c);
					firstvt.push_back(fv);
					fv.clear();
					break;
				}
			}
		}
		else {
			 index= find_bigchar(firstvt, a[0]);
			for (int i = 3; i < a.size(); i++)//�ҵ���һ���ս��
			{
				if (!(a[i] <= 'Z' && a[i] >= 'A') && a[i] != ' ')
				{
					if (!(find_smallchar(firstvt, a[i], index)))//û���ҵ�
					{
						firstvt[index][1]+=a[i];
					}
					break;
				}
			}
		}
	}
	//��ʼ�����
	while (1)
	{
		flag = 0;
		ifs.clear();//�����ǰ��״̬
		ifs.seekg(0, ios::beg);//�ļ���ָ��ص���ͷ
		while (getline(ifs, a))
		{
			
			if (a[3] != a[0] && a[3] <= 'Z' && a[3] >= 'A')
			{
				index = find_bigchar(firstvt, a[0]);
				firstsize = find_bigchar(firstvt, a[3]);
				for (int i = 0; i < firstvt[firstsize][1].size(); i++)
				{
					if (!find_smallchar(firstvt,firstvt[firstsize][1][i],index))//û�ҵ�
					{
						firstvt[index][1] += firstvt[firstsize][1][i];
						flag = 1;//��ʾ����ӣ�����ѭ��
					}
				}
		   }
		}
		if (flag == 0)
		{
			break;
		}
	}
	ifs.close();
	cout << "firstvt���ϴ�ӡ�����" << endl;
	for (int i = 0; i < firstvt.size(); i++)
	{
		cout << "firstvt(" << firstvt[i][0] << ")= {"; 
		for (int j = 0; j < firstvt[i][1].size(); j++)
		{
			cout << firstvt[i][1][j] << "  ";
		}
		cout<< "}" << endl;
		
	}

}
//����ÿһ�����ս����lastVT���ϣ�����ӡ����
void Get_lastvt()
{
	//ɨ���ķ�
	int index;
	int firstsize = 0;
	int flag = 0;//�жϼ����Ƿ��ٱ仯
	string c;
	vector<string> fv;
	string a;//���ж��ļ�
	ifstream ifs;
	ifs.open("split.txt", ios::in);
	while (getline(ifs, a))
	{
		if (find_bigchar(lastvt, a[0])==-1)
		{
			for (int i = a.size()-1; i>=3; i--)//�ҵ����һ���ս��
			{
				if (!(a[i] <= 'Z' && a[i] >= 'A') && a[i] != ' ')
				{
					c = a[0];
					fv.push_back(c);
					c = a[i];
					fv.push_back(c);
					lastvt.push_back(fv);
					fv.clear();
					break;
				}
			}
		}
		else {
			index = find_bigchar(lastvt, a[0]);
			for (int i = a.size() - 1; i >= 3; i--)//�ҵ����һ���ս��
			{
				if (!(a[i] <= 'Z' && a[i] >= 'A') && a[i] != ' ')
				{
					if (!(find_smallchar(lastvt, a[i], index)))
					{
						lastvt[index][1] += a[i];
					}
					break;
				}
			}
		}
	}
	//��ʼ�����
	while (1)
	{
		flag = 0;
		ifs.clear();
		ifs.seekg(0, ios::beg);//�ļ���ָ��ص���ͷ
		while (getline(ifs, a))
		{
			if (a[a.size()-1] != a[0] && a[a.size() - 1] <= 'Z' && a[a.size() - 1] >= 'A')
			{
				index = find_bigchar(lastvt, a[0]);
				firstsize = find_bigchar(lastvt, a[a.size() - 1]);
				for (int i = 0; i < lastvt[firstsize][1].size(); i++)
				{
					if (!find_smallchar(lastvt, lastvt[firstsize][1][i], index))
					{
						lastvt[index][1] += lastvt[firstsize][1][i];
						flag = 1;//��ʾ����ӣ�����ѭ��
					}
				}
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
	ifs.close();
	cout << "lastvt���ϴ�ӡ�����" << endl;
	for (int i = 0; i < lastvt.size(); i++)
	{
		cout << "lastvt(" << lastvt[i][0] << ")= {";
		for (int j = 0; j < lastvt[i][1].size(); j++)
		{
			cout << lastvt[i][1][j] << "  ";
		}
		cout << "}" << endl;

	}

}
//����������ȹ�ϵ��,����ӡ����
void Get_table()
{

    //��ʼ��������ȷ����ȹ�ϵ
	int k1,k2,index;
	vector<char> hang(vt.size() + 1,' ');//+1ָ����#,��ʼ��Ϊ�ո�

	for (int i = 0; i < vt.size() + 1; i++)
	{
		table.push_back(hang);
	}
	
	string a;
	ifstream ifs;
	ifs.open("split.txt", ios::in);
	while (getline(ifs, a))
	{
		if (a.size() >= 5)
		{
			for (int i = 3; i < a.size() - 1; i++)
			{
				if (!(a[i] <= 'Z' && a[i] >= 'A')&&!(a[i+1] <= 'Z' && a[i+1] >= 'A')&&a[i]!=' '&&a[i+1]!=' ')
				{
					k1 = find_vt(vt, a[i]);
					k2 = find_vt(vt, a[i+1]);
					if (k1 == -1 || k2 == -1)
					{
						cout << "���ֲ�Ӧ�ô��ڵ��ս����EORROR" << endl;
						return;
					}
					table[k1][k2] = '=';

				}
				if (!(a[i] <= 'Z' && a[i] >= 'A') && (a[i + 1] <= 'Z' && a[i + 1] >= 'A') && a[i] != ' ')
				{
					//a[i]<firstvt(a[i+1])�е�����Ԫ��
					index = find_bigchar(firstvt, a[i + 1]);
					for (int j = 0; j < firstvt[index][1].size(); j++)
					{
						k1 = find_vt(vt, a[i]);
						k2 = find_vt(vt, firstvt[index][1][j]);
						table[k1][k2] = '<';
						
					}
				}
				if (!(a[i+1] <= 'Z' && a[i+1] >= 'A') && (a[i] <= 'Z' && a[i] >= 'A') && a[i+1] != ' ')
				{
					//lastvt(a[i])�е�����Ԫ��>a[i+1]
					index = find_bigchar(lastvt, a[i]);
					for (int j = 0; j < lastvt[index][1].size(); j++)
					{
						k2 = find_vt(vt, a[i+1]);
						k1 = find_vt(vt, lastvt[index][1][j]);
						table[k1][k2] = '>';

					}
				}
			}
			if (a.size() >= 6)
			{
				for (int i = 3; i < a.size() - 2; i++)
				{
					if (!(a[i] <= 'Z' && a[i] >= 'A') && !(a[i + 2] <= 'Z' && a[i + 2] >= 'A') && a[i] != ' ' && a[i + 2] != ' ')
					{
						k1 = find_vt(vt, a[i]);
						k2 = find_vt(vt, a[i + 2]);
						if (k1 == -1 || k2 == -1)
						{
							cout << "���ֲ�Ӧ�ô��ڵ��ս����EORROR" << endl;
							return;
						}
						table[k1][k2] = '=';

					}
				}
			}
		}
		//����#
		//��#��E
	for (int j = 0; j < firstvt[0][1].size(); j++)
		{
			k1 = vt.size();
			k2 = find_vt(vt, firstvt[0][1][j]);
			table[k1][k2] = '<';

		}
		
			
	for (int j = 0; j < lastvt[0][1].size(); j++)
		{
			k2 = vt.size();
			k1 = find_vt(vt, lastvt[0][1][j]);
			table[k1][k2] = '>';

		}
		
	}
	//��ӡtable��
	cout << "    ";
	for (int i = 0; i < vt.size(); i++)
	{
		cout << vt[i] << "   ";
	}
	cout << "#" << endl;
	for (int i = 0; i < vt.size()+1; i++)
	{
		if (i == vt.size())
		{
			cout << '#' << "   ";
			for (int j = 0; j < vt.size() ; j++)
			{
				cout << table[i][j] << "   ";
			}
			cout << '=';
			table[i][i] = '=';
			cout << endl;
			break;
		}
		cout << vt[i] << "   ";
		for (int j = 0; j < vt.size()+1; j++)
		{
			cout << table[i][j] << "   ";
		}
		cout << endl;
	}

	ifs.close();
}
//������ȷ�����ִ�У���ӡִ�й���
void analysis()
{

	vt.push_back('#');
	int i=0;//�������
	int k = 0;//����ջջ��ָ��
	cout << "��������Ҫ��������(��#��β)��" << endl;
	cin >> inputs;
	cout << "����" << "   " << "����" << "   " << "����ջ" << "   " << "ʣ���Ӵ�" << endl;
	while (1)
	{
		k = 0;
		if (inputs == "")
		{
			break;
		}
		cout << " " << i << "     ";
		if (inputs[0] <= 'Z' && inputs[0] >= 'A')
		{
			movein();
		}
		else {
			if (find_vt(vt, inputs[0]) == -1)
			{
				cout << "�����Ӵ����зǷ��ַ���ERROR" << endl;
				input_flag = 0;
				if (input_flag == 0)
				{
					cout << "�����Ӵ��Ƿ�" << endl;
					return;
				}
			}
			while (1)
			{
				if (ST[k] <= 'Z' && ST[k] >= 'A')
				{
					k += 1;
				}
				else break;
			}
			if (com_twochars(inputs[0],ST[k] ) == '=' || com_twochars(inputs[0], ST[k]) == '>')
			{
				movein();
			}
			else if (com_twochars(inputs[0], ST[k]) == '<' )
			{
				reduce(k);
				if (input_flag == 0)
				{
					cout << "�����Ӵ��Ƿ�" << endl;
					return;
				}
			}
			else if (com_twochars(inputs[0], ST[k]) == ' ')
			{
				input_flag = 0;
				if (input_flag == 0)
				{
					cout << "������ȹ�ϵ����û�����ֱȽϹ�ϵ��ERROR,�����Ӵ��Ƿ�" << endl;
					return;
				}
			}
		}
		i++;
	}
}

//������
void main()
{
	input_file();//�û������ķ�
	split();//����ķ�
	if (check_two_bigchar())
	{
		cout << "���ķ���������ķ����������" << endl;
		return;
	}
	read_char();//��ӡ���ս�����ս��
	Get_firstvt();
	Get_lastvt();
	Get_table();
	analysis();
}
