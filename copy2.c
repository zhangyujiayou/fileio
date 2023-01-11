#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
//copy file1 to file2
/*
 * ./copy 1.txt 2.txt
 * argc = 3
 * argv[0] = "./copy"
 * argv[1] = "1.txt"
 * argv[2] = "2.txt"
 */

int main(int argc,char **argv)
{
	int fd_old, fd_new,readlen,writelen;
	char buf[1024];
	
	//进行参数的判断
	if (3!=argc)
		{
			printf("use:./copy oldfilename newfilename\n");
			return -1;
		}
	

	//进行参数的判断
	if (3==argc)
		{
			//进行复制的工作
			
			//1.首先打开老文件,创建一个新的文件并且打开新的文件
			fd_old=open(argv[1],O_RDWR,S_IRWXU);
			if (-1==fd_old)
				{
					printf("%s is no to open !\n",argv[1]);
					return -1;
				}
			fd_new=open(argv[2],O_RDWR|O_CREAT,S_IRWXU);
			if (-1==fd_new)
				{
					printf("%s is no to creat or open !\n",argv[2]);
					return -1;
				}
			
			//2.将老文件拷贝成新文件
			/*循环的进行：将老文件的内容读出来*/
			while ((readlen=read(fd_old,buf,1024))>0)
				{
					/*将从老文件读出来的内容在入到新文件里面去*/
					writelen=write(fd_new,buf,readlen);
					printf("debug: read from %s %d byte and write %d byte to %s\n",\
							argv[1],readlen,writelen,argv[2]);
					if (readlen!=writelen)
						{
							printf("%s is copy failed !\n",argv[2]);
							return -1;
						}
				}
			printf("%s copy done !\n",argv[2]);
			
			//3.关闭文件
			close(fd_old);
			close(fd_new);
			
		}
	return 0;
}
















































