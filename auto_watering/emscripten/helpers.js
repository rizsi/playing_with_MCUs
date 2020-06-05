function buttonHandler(elementId, cIndex)
{
	var dom=document.getElementById(elementId);
	var ctx={};
	ctx.cIndex=cIndex;
	dom.addEventListener("click", function(){
		buttonPressed(this.cIndex);
	}.bind(ctx)); 
}
function signalHandler(elementId, cIndex)
{
	var dom=document.getElementById(elementId);
	var ctx={};
	ctx.cIndex=cIndex;
	dom.addEventListener("click", function(){
		signalEvent(this.cIndex);
	}.bind(ctx)); 
}

