package com.rizsi.kicad;

public class KicadPcbObjectString extends KicadPcbObject
{
	public String s;
	
	public KicadPcbObjectString(String s) {
		super();
		this.s = s;
	}

	@Override
	public void print() {
		System.out.print(""+s);
	}

	@Override
	public String getType() {
		return "";
	}

}
