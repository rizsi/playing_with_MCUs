package com.rizsi.kicad;

import java.util.Stack;

public class KicadPcbParser {
	private String source;

	public KicadPcbParser(String source) {
		super();
		this.source = source;
		current.push(root);
	}
	public KicadPcbObjectCompound root=new KicadPcbObjectCompound(0);
	public Stack<KicadPcbObjectCompound> current=new Stack<>();
	private StringBuilder charCollector=new StringBuilder();
	public void parse() {
		for(int i=0;i<source.length();++i)
		{
			char c=source.charAt(i);
			if(c=='(')
			{
				appendCollectedString();
				KicadPcbObjectCompound parent=current.peek();
				KicadPcbObjectCompound obj=new KicadPcbObjectCompound(i);
				current.push(obj);
				parent.pieces.add(obj);
				// Open object
			}else if(c==')')
			{
				current.peek().setCloseCharacterIndex(i);
				appendCollectedString();
				current.pop();
				// Close object
			}else if(Character.isWhitespace(c))
			{
				appendCollectedString();
				// Object separator
			}else
			{
				charCollector.append(c);
			}
		}
	}
	private void appendCollectedString() {
		if(charCollector.length()>0)
		{
			current.peek().pieces.add(new KicadPcbObjectString(charCollector.toString()));
		}
		charCollector.delete(0, charCollector.length());
	}
	public void print() {
		for(KicadPcbObject o: current)
		{
			o.print();
		}
	}
	public void validate() {
		if(current.size()!=1)
		{
			throw new RuntimeException("Error parsing: some object not closed");
		}
	}
}
