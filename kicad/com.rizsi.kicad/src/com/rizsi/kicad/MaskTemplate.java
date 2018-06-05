package com.rizsi.kicad;

import java.io.StringWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class MaskTemplate {
	StringWriter output=new StringWriter();
	private List<KicadPcbObjectCompound> toCopy=new ArrayList<>();
	public KicadPcbObjectCompound appendInto;
	private Map<Integer, Integer> toDeleteCoordinates=new TreeMap<>();
	public void copyToMask(KicadPcbObjectCompound segment)
	{
		toCopy.add(segment);
	}
	private void writeObject(Object o) {
		output.append(""+o);
	}
	private void write(String string) {
		output.append(string);
	}
	public String generateOutput(String source)
	{
		boolean skipWhitespaces=false;
		for(int i=0;i<source.length();++i)
		{
			char c=source.charAt(i);
			Integer deleteEnd=toDeleteCoordinates.get(i);
			if(deleteEnd!=null)
			{
				i=deleteEnd;
				skipWhitespaces=true;
				continue;
			}
			if(skipWhitespaces&&Character.isWhitespace(c))
			{
				// Skip whitespaces after the last deleted object
			}else
			{
				output.append(c);
				skipWhitespaces=false;
			}
			if(i==appendInto.closeCharacterIndex-1)
			{
				skipWhitespaces=false;
				for(KicadPcbObjectCompound segment: toCopy)
				{
					write("  (gr_line (start ");
					writeObject(segment.get("start").getString(1));
					write(" ");
					writeObject(segment.get("start").getString(2));
					write(") (end ");
					writeObject(segment.get("end").getString(1));
					write(" ");
					writeObject(segment.get("end").getString(2));
					write(") (layer ");
					writeObject(segment.get("layer").getString(1).substring(0,1));
					write(".Mask) (width ");
					writeObject(segment.get("width").getString(1));
					write("))\n");
				}
			}
		}
		return output.toString();
	}
	public void addDelete(KicadPcbObjectCompound secondLevel) {
		toDeleteCoordinates.put(secondLevel.openCharacterIndex, secondLevel.closeCharacterIndex);
	}
}
