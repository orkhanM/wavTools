fid=fopen('new.dat');
a=fscanf(fid,'%f',[1,inf]);
fclose(fid);

time=(1/44100)*length(a);
t=linspace(0,time,length(a));
plot(t,a)

pause
