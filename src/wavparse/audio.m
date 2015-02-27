#! /usr/bin/octave -qf

arg_list = argv();
[chirp,fs]=wavread(arg_list{1});

left=chirp(:,1);
#right=chirp(:,2);

#time=(1/fs)*length(left);
#tleft=linspace(0,time,length(left));
#tright=linspace(0,time,length(right));
#plot(tleft,left)
#xlabel('time(sec)');
#ylabel('relative signal strength')

save -ascii src/wavparse/wav.dat left;
#pause
