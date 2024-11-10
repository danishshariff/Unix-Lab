 
 #include<iostream>
 #include<unistd.h>
 intmain(intargc,char*argv[]){
 if(argc!=3){
 std::cerr<<"Usage:"<<argv[0]<<"source_filetarget_file"<<std::endl;
 return1;
 }
 constchar*source_file=argv[1];
 constchar*target_file=argv[2];
 if(link(source_file, target_file)==0){
 std::cout<<"Hardlinkcreated:"<<target_file<<"->"<<source_file<<std::endl;
 return0;
 }else{
 perror("Errorcreatinghardlink");
 return2;
 }
 }