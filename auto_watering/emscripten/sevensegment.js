/** Seven segment output implemented in a HTML canvas */
class SevenSegment {
  constructor(domObject) {
    this.domObject = domObject;
    this.state=[true, true, true, true,  true, true, true, true];
    this.update();
  }
  update() {
	var dotR=3;
	var margin=2;
	var canvas=this.domObject;
	var w=canvas.width-dotR*2-1;
	var h=canvas.height-dotR*2-1;
	var ctx = canvas.getContext("2d");
	ctx.fillStyle = "rgba(0, 0, 0, 0)";
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.beginPath();
	ctx.lineWidth=3;
	if(this.state[0])
	{
		ctx.moveTo(margin, margin);
		ctx.lineTo(w, margin);
		ctx.stroke(); 
	}
	if(this.state[1])
	{
		ctx.moveTo(w, margin);
		ctx.lineTo(w, h/2);
		ctx.stroke(); 
	}
	if(this.state[2])
	{
		ctx.moveTo(w-margin, h/2);
		ctx.lineTo(w-margin, h);
		ctx.stroke(); 
	}
	if(this.state[3])
	{
		ctx.moveTo(margin, h);
		ctx.lineTo(w, h);
		ctx.stroke(); 
	}
	if(this.state[4])
	{
		ctx.moveTo(margin, h/2);
		ctx.lineTo(margin, h);
		ctx.stroke(); 
	}
	if(this.state[5])
	{
		ctx.moveTo(margin, margin);
		ctx.lineTo(margin, h/2);
		ctx.stroke(); 
	}
	if(this.state[6])
	{
		ctx.moveTo(margin, h/2);
		ctx.lineTo(w-margin, h/2);
		ctx.stroke(); 
	}
	if(this.state[7])
	{
		ctx.fillStyle = "rgba(0, 0, 0, 1)";
		ctx.beginPath();
		ctx.arc(w+dotR, h+dotR, dotR, 0, 2 * Math.PI);
		ctx.fill(); 
//		ctx.moveTo(0, 0);
//		ctx.lineTo(0, h/2);
//		ctx.stroke(); 
	}
  }
  setPattern(pattern)
  {
	for(var i=0;i<8;++i)
	{
		this.state[i]=(pattern&1)!=0;
		pattern>>=1;
	}
//	this.state[7]=true;
	this.update();
  }
}

function createSevenSegmentDigits(domParent, width, height, n, addToArray)
{
	var created=[];
	for(var i=0;i<n;++i)
	{
		var c=document.createElement("canvas");
		c.width=width;
		c.height=height;
		domParent.appendChild(c);
		created.push(new SevenSegment(c));
	}
	for(var i=0;i<created.length;++i)
	{
		addToArray.push(created[created.length-i-1]);
	}
	return;
}


