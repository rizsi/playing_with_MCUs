package com.rizsi.kicad;

import java.util.ArrayList;
import java.util.List;

public class KicadPcbObjectCompound extends KicadPcbObject
{
	List<KicadPcbObject> pieces=new ArrayList<>();
	public int closeCharacterIndex;
	public int openCharacterIndex;

	public KicadPcbObjectCompound(int openCharacterIndex) {
		super();
		this.openCharacterIndex = openCharacterIndex;
	}

	public void print() {
		System.out.print("\n(");
		boolean first=true;
		for(KicadPcbObject o: pieces)
		{
			System.out.print(first?"":" ");
			o.print();
		}
		System.out.println(")");
	}

	public String getType() {
		return ((KicadPcbObjectString)pieces.get(0)).s;
	}

	public KicadPcbObjectCompound get(String type) {
		for(KicadPcbObject o: pieces)
		{
			if(type.equals(o.getType()))
			{
				return (KicadPcbObjectCompound)o;
			}
		}
		return null;
	}

	public String getString(int i) {
		return ((KicadPcbObjectString)pieces.get(i)).s;
	}

	public void setCloseCharacterIndex(int i) {
		this.closeCharacterIndex=i;
	}

}
