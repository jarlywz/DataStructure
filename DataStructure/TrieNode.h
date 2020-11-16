#pragma once
using namespace std;
const int N = 26;

struct STrieNode
{
	char val;
	STrieNode** next;
	int count;
	
	STrieNode(char c)
	{
		this->val = c;
		this->next = new STrieNode*[N];
		for (int i = 0; i< N; ++i)
		{
			this->next[i] = nullptr;
		}

		this->count = 0;
	}
};

STrieNode* root;

void Insert(string s)
{
	STrieNode* p = root;
	for (int i = 0; i < s.size(); ++i)
	{
		int c = s[i] - 'a';
		if (!p->next[c])
		{
			p->next[c] = new STrieNode(c);
		}

		p = p->next[c];
	}

	p->count++;
}

int Query(string s)
{
	STrieNode* p = root;
	for (int i = 0; i < s.size(); i++)
	{
		int c = s[i] - 'a';
		if (!p->next[c])
		{
			return 0;
		}

		p = p->next[c];
	}

	return p->count;
}