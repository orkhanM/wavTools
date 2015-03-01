[chirp,fs]=wavread('hello.wav');

left=chirp(:,1);
right=chirp(:,2);

time=(1/fs)*length(left);
tleft=linspace(0,time,length(left));
tright=linspace(0,time,length(right));
plot(tleft,left)
xlabel('time(sec)');
ylabel('relative signal strength')

save -ascii wav.dat left;
pause
