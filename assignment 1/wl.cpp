//
// File: wl.cpp
// 
//  Description: word locator
//  Student Name: Sung Joon Lim
//  UW Campus ID: 9075324815
//  email: lim62@wisc.edu

#include "wl.h"

//recursive
void bitree::rm_tree(child *node)
{
	if (node != NULL)
	{
		rm_tree(node -> right);
		rm_tree(node -> left);
		delete node;
	}
}

void bitree::add (std::string str, child *node, int index)
{
	if (str == node -> word)
	{
		node -> indexList.push_back(index);
	}
	else if (str < node -> word)
	{
		if (node -> word != "")
		{
			// recursive
			add(str, node -> left, index);
		}
		else
		{
			// create new child
			node -> left = new child;
			node -> left -> word = str;
			node -> left -> indexList.push_back(index);
			node -> left -> left = NULL;
			node -> left -> right = NULL;
		}
	}
	else if (str >= node -> word)
	{
		if (node -> right)
		{
			// recursive
			add(str, node -> right, index);
		}
		else
		{
			// new child
			node -> right = new child;
			node -> right -> word = str;
			node -> right -> indexList.push_back(index);
			node -> right -> right = NULL;
			node -> right -> left = NULL;
		}
	}
}

child *bitree::find(std::string str, child *node, int index)
{
	if (node != NULL)
	{
		if (str == node -> word)
		{
			return (node);
		}
		if (str < node -> word)
		{
			return find(str, node -> left, index);
		}
		else
		{
			return find(str, node -> right, index);
		}
	}
	else
	{
		return (NULL);
	}
}

void bitree::add(std::string str, int index)
{
	if (root != NULL)
	{
		add(str, root, index);
	}
	else
	{
		root = new child;
		root -> word = str;
		root -> indexList.push_back(index);
		root -> left = NULL;
		root -> right = NULL;
	}
}

child *bitree::find(std::string str, int index)
{
	return (find(str, root, index));
}

void bitree::rm_tree()
{
	rm_tree(root);
}

bitree* init_tree(bitree *wordTree)
{
	bitree	*temp;
	temp = wordTree;
	wordTree -> rm_tree();
	delete wordTree;
	temp = new bitree;
	wordTree = temp;
	return (wordTree);
}

std::vector<std::string> parse_space(std::string str)
{
  std::stringstream		stream(str);
  std::string			curr;
  std::vector<std::string>	result;
  while (stream >> curr) 
  {
	  result.push_back(curr);
  }
  return (result);
}

std::string to_lowcase (std::string str)
{
	unsigned int i = 0;
	while (i < str.length())
	{
		str[i] = tolower(str[i]);
		i++;
	}
	return (str);
}

std::string to_trim(std::string str)
{
	if (str.length() > 1)
	{
		char last = str[str.length() - 1];
		// check
		if (!isalpha(last) && !isdigit(last))
		{
			str = str.substr(0, str.length() - 1);
		}
	}
	return (str);
}
int main()
{
	bitree		*wordTree;
	std::string	initInput;
	std::string	whitespace;
	bool		argFlag;
	int		index;

	wordTree = new bitree;
	whitespace = " ";
	argFlag = false;
	index = 1;

	std::cout << ">";
	while (getline(std::cin, initInput))
	{
		argFlag = false;
		// divide by space
		std::vector<std::string>	input;
		input = parse_space(initInput);
		// change to alphabet to lowercase
		unsigned int i = 0;
		while (i < input.size())
		{
			input[i] = to_lowcase(input[i]);
			i++;
		}
		// check input, case: load
		if (input[0] == "load" && input.size() == 2)
		{
			std::string	file = input[1];
			std::ifstream	inputFile(file.c_str());
			std::string	curr;
			if (inputFile.is_open())
			{
				wordTree = init_tree(wordTree);
				printf ("test 1");
				index = 1;
				while (getline(inputFile, curr))
				{
					std::vector<std::string> words;
					words = parse_space(curr);
					unsigned int j = 0;
					while (j < words.size())
					{
						words[j] = to_lowcase(words[j]);
						words[j] = to_trim(words[j]);
						wordTree -> add(words[j], index);
						index++;
						j++;
					}	
				}
				wordTree -> is_empty = false;
				inputFile.close();
			}
			else
			{
				std::cout << "ERROR: Invalid command" << std::endl;
			}
		}
		// case: locate
		else if (input[0] == "locate" && input.size() == 3)
		{
			std::string userWord = input[1];
			std::string userinputIndex = input[2];
			// check user input word
			unsigned int i = 0;
			while (i < userWord.size())
			{
				// check
				if (!isalpha(userWord[i]) && !isdigit(userWord[i]))
				{
					std::cout << "ERROR: Invalid command" 
			
						<< std::endl;
					argFlag = true;
					break;
				}
				i++;
			}
			// check user input index
			if (argFlag == false)
			{
				unsigned int i = 0;
				while (i < userinputIndex.size())
				{
					if(!isdigit(userinputIndex[i]))
					{
						std::cout << "ERROR: Invalid command" 
							<< std::endl;
						argFlag = true;
						break;
					}
					i++;
				}

			}
			// find word
			unsigned int userIndex = atoi(userinputIndex.c_str());
			if (argFlag == false)
			{
				if (wordTree -> is_empty == false)
				{
					struct child *currChild = wordTree 
						-> find(userWord, userIndex);
					if (currChild != NULL)
					{
						if (currChild -> indexList.size() 
								>= userIndex)
						{
						//check
						std::cout << currChild 
							-> indexList[userIndex - 1] 
							<< std::endl;
						}
						else
						{
						std::cout << "No matching entry" 
							<< std::endl;
						}
					}
					else
					{
						std::cout << "No matching entry" 
							<< std::endl;
					}
				}
		
				else
				{
					std::cout << "No matching entry" << std::endl;
				}
			}
		}
		// case: new
		else if (input[0] == "new" && input.size() == 1)
		{
			wordTree = init_tree(wordTree);
			index = 1;
		}
		// case: end
		else if (input[0] == "end" && input.size() == 1)
		{
			return (0);
		}
		else
		{
			std::cout << "ERROR: Invalid command" << std::endl;
		}
		std::cout << ">";
	}
	return (0);
}
