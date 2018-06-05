package com.rizsi.kicad;

import java.io.File;

/**
 * Processor class for Kicad that copies Cu layer to the mask layer.
 * 
 * Designed to be used to make it possible to add solder to copper on a fabbed PCB to
 * increase the possible amps on the lines.
 * 
 * This is just a hobby project with no specific quality management so use it 
 * on your own responsibility.
 * 
 * @author rizsi
 *
 */
public class KicadProcessor {
	public static void main(String[] args) throws Exception {
		new KicadProcessor().run(args);
	}

	private void run(String[] args) throws Exception {
		System.out.println("Kicad file processor. First argument is the kicad_pcb file to process");
		System.out.println("Copies all traces with 1.5mm width from F.Cu and B.Cu to the F.Mask and B.Mask layers.");
		File f=new File(args[0]);
		String s=UtilFile.loadAsString(f);
		KicadPcbParser p=new KicadPcbParser(s);
		p.parse();
		p.validate();
		MaskTemplate t=new MaskTemplate();
		for(KicadPcbObject o: p.root.pieces)
		{
			for(KicadPcbObject secondLevel: ((KicadPcbObjectCompound) o).pieces)
			{
				if(matches(secondLevel, "segment", "F.Cu", "B.Cu"))
				{
					t.copyToMask((KicadPcbObjectCompound)secondLevel);
				}
				if(matches(secondLevel, "gr_line", "F.Mask", "B.Mask"))
				{
					t.addDelete((KicadPcbObjectCompound)secondLevel);
				}
			}
			t.appendInto=(KicadPcbObjectCompound)o;
		}
		String processed=t.generateOutput(s);
		UtilFile.saveAsFile(f, processed);
	}

	private boolean matches(KicadPcbObject k, String type, String... layerName) {
		if(k instanceof KicadPcbObjectCompound)
		{
			KicadPcbObjectCompound c=(KicadPcbObjectCompound) k;
			String _type=c.getType();
			if(type.equals(_type))
			{
				String layer=c.get("layer").getString(1);
				for(String l: layerName)
				{
					if(l.equals(layer))
					{
						if("1.5".equals(c.get("width").getString(1)))
						return true;
					}
				}
			}
		}
		return false;
	}
}
