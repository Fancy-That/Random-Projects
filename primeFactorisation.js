let g=(a,b)=>a%b?g(b,a%b):b,pFactor=(_,$=[],x,i=_)=>{for(;--i;)x=g(_,i),x>1?($.push(x),x=pFactor(x)[0],_/=x,i=_):0;return[_,...$]};
