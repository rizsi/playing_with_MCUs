function buttonHandler(elementId, cIndex)
{
	var dom=document.getElementById(elementId);
	var ctx={};
	ctx.cIndex=cIndex;
	dom.addEventListener("click", function(){
		buttonPressed(this.cIndex);
	}.bind(ctx)); 
}

class Led {
  constructor(domObject) {
    this.domObject = domObject;
    this.state=false;
    this.update();
  }
  update() {
//	console.info("Update LED! "+this.state);
	if(this.state)
	{
		this.domObject.className="led-on";
	}else
	{
		this.domObject.className="led-off";
	}
  }
  setPattern(pattern)
  {
	this.state=pattern!=0;
	this.update();
  }
}

