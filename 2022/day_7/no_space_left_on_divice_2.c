// https://adventofcode.com/2022/day/7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dir_l 20 // max char lenght of dir name
#define dir_max_size 100000 // only account for dir with at most this total size

typedef struct TreeNode {
  char name[dir_l];
  TreeNode* parent;
  int ls_flag; // 0 if not ls'ed
  int sum;
  char child_name[50][dir_l]; // https://www.programiz.com/c-programming/library-function/string.h/strcmp
  TreeNode* child[50];
} TreeNode;

// [dir_sum, nested_dir_a, nested_dir_b, 0, ...]
// reccurs sum for each nested sum
int recursiveSum(TreeNode* _ptr, int* sum)
{
  int dir_sum=0;
  int output_sum;
  int child_index=0;

  while ( _ptr->child_name[child_index][0] ) {
    dir_sum += recursiveSum(_ptr->child[child_index++], sum);
  }
  output_sum = _ptr->sum + dir_sum;
  *sum += output_sum;
  _ptr->sum=output_sum;
  return output_sum;
}

void findDeleteDir(TreeNode* _ptr, int* delete_sum, int* dir_sum, char dir_name[dir_l])
{
  int child_index=0;

  while ( _ptr->child_name[child_index][0] ) {
    findDeleteDir(_ptr->child[child_index++], delete_sum, dir_sum, dir_name);
  }
  if ( _ptr->sum >= *delete_sum && _ptr->sum < *dir_sum ) {
    *dir_sum = _ptr->sum;
    memcpy(dir_name, _ptr->name, dir_l);
  }
}

void recursiveFree(TreeNode* _ptr)
{
  int child_index=0;

  while ( _ptr->child_name[child_index][0] ) {
    recursiveFree(_ptr->child[child_index++]);
  }
  free(_ptr);
}

TreeNode* createTreeNode(const char* _name)
{
  // [dir_name, *parent_dir, dir_sum, *nested_dir, *nested...]
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

  // initialize current ptr
  strcpy(node->name, _name);
  node->sum=0;
  node->ls_flag=0;
  memset(node->child, 0, 50);

  return node;

}

void createChild(TreeNode* _parent, char* _child_name)
{
  int i=0;

  TreeNode* child_node = createTreeNode(_child_name);

  // count current number of child nodes
  while ( _parent->child[i++] ) {}
  // populate child node
  strcpy(_parent->child_name[i-1], _child_name);
  _parent->child[i-1]=child_node;
  child_node->parent=_parent;

}

int main(int argc, char** argv)
{

  FILE* ptr = fopen(argv[1], "r");
  char str[100];

  int final_sum=0;
  int delete_sum;
  int delete_size=70000000;
  char delete_dir[dir_l];

  //** tree **//
  TreeNode* root_node = createTreeNode("/");
  TreeNode* pwd=root_node;

  //** directories **//
  int dir_name_check=5;
  char dir_name[dir_l]={0};
  int cd_dir_index=0;

  //** ls **//
  // nested directories
  int nested_dir_name_check=4;
  char nested_dir_name[dir_l]={0};

  // dir sum
  int dir_sum=0;
  int dir_sum_check=0;
  char dir_sum_string[dir_l]={0};

  while ( fgets(str, 100, ptr) != NULL ) {
    // $ logic
    if ( str[0] == '$') {
      // cd logic
      if ( str[2] == 'c' ) {
        while ( str[dir_name_check] != '\n' ) {
          dir_name[dir_name_check-5] = str[dir_name_check];
          ++dir_name_check;
        }
        //printf("pwd %s cd: %s\n", pwd->name, dir_name);

        if ( dir_name[0] == '.' ) {
          pwd=pwd->parent;
        } else {
          while ( strcmp(dir_name, pwd->child_name[cd_dir_index++] ) ) {}
          pwd=pwd->child[cd_dir_index-1];
          cd_dir_index=0;
        }

        dir_name_check=5; // reset dir byte start
        dir_sum=0; // reset dir sum
      }
      // ls logic
      else if ( str[2] == 'l' ) {
        pwd->ls_flag=1;
        //printf("pwd %s ls: %s\n", pwd->name, pwd->name);
      }
    }
    // display logic
    else if ( pwd->ls_flag ){
      // nested dir
      if ( str[0] == 'd' ) {
        while ( str[nested_dir_name_check] != '\n' ) {
          nested_dir_name[nested_dir_name_check-4] = str[nested_dir_name_check];
          ++nested_dir_name_check;
        }
      createChild(pwd, nested_dir_name);

      //printf("pwd %s nested: %s\n", pwd->name, nested_dir_name);
      nested_dir_name_check=4; // reset nested dir byte start
      }
      // file sum logic
      else {
        while ( str[dir_sum_check] != ' ' ) {
          dir_sum_string[dir_sum_check] = str[dir_sum_check];
          ++dir_sum_check;
        }
      dir_sum += atoi(dir_sum_string);
      pwd->sum += dir_sum;
      //printf("pwd %s sum: %d\n", pwd->name, pwd->sum);
      dir_sum_check=0; // reset nested dir byte start
      dir_sum=0;
      }
    }

    // empty all buffers
    for ( int i=0; i < dir_l; i++ ) {
      dir_name[i]=0;
      nested_dir_name[i]=0;
      dir_sum_string[i]=0;
    }
    // iterate input line number (not currently used)
  }
  fclose(ptr);

  // calculate dir sums
  recursiveSum(root_node, &final_sum);

  // find required storage and min/max dir to delete
  delete_sum = 30000000 + root_node->sum - 70000000;
  findDeleteDir(root_node, &delete_sum, &delete_size, delete_dir);
  printf("%d\n", delete_size);

  // free all ptr
  recursiveFree(root_node);
  return 0;
}
