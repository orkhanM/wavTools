fid=fopen('wav.dat');
a=fscanf(fid,'%i',[1,inf]);

length(a)
time=(1/44100)*length(a);
t=linspace(0,time,length(a));
plot(t,a)

pause
