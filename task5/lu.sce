x=[4,4.11111,4.22222,4.33333,4.44444,4.55556,4.66667,4.77778,4.88889,5];
y=[97.0013,104.281,111.927,119.919,128.307,137.043,146.186,155.712,165.653,175.999];
p=poly([91.3007,-60.5634,15.4992],'k','c');
xx=4:0.01:5;pp=horner(p,xx);plot(xx,pp,'b');
ee=poly([1,0,0,1],'k','c');
e=horner(ee,xx);plot(xx,e,'r');
d1=horner(p,x)-horner(ee,x);
d1=d1.^2;
d=sqrt(sum(d1)/size(d1,2));
plot(x,y,'b*');
xgrid();
xtitle('lu','X', 'Y');