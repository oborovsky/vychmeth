x=[0,0.111111,0.222222,0.333333,0.444444,0.555556,0.666667,0.777778,0.888889,1];
p=poly([-0.0167292,1.85703,-0.827647],'k','c');
xx=0:0.01:1;pp=horner(p,xx);plot(xx,pp,'b');
s=sin((%pi*xx)/2);plot(xx,s,'r');
d1=horner(p,x)-sin(%pi*x/2);
d1=d1.^2;
d=sqrt(sum(d1)/size(d1,2));
xgrid();
xtitle('lu','X', 'Y');
