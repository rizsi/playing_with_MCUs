

import java.util.TreeMap;

public class Divisors {
	static class Range
	{
		int row;
		int col;
		int readout;
		int minLimit;
		int maxLimit=-1;
		int index;	// Index of the button in the uC application
		char ch; // Label of the button
	}
	public static void main(String[] args) {
		int indexes[]={1, 2, 3,
						4, 5, 6,
						7, 8, 9,
						10, 0, 11
		};
		char chars[]={'1', '2', '3',
				'4', '5', '6',
				'7', '8', '9',
				'*', '0', '#'
		};
/*
1 - 1.02 V
 2 - 1.22 V
 3 - 1.46 V
 4 - 1.71 V
 5 - 2.02 V
 6 - 2.42 V
 7 - 2.81 V
 8 - 3.11 V
 9 - 3.31 V
 0 - 3.91 V
 * - 3.60 V
kettős kereszt - 3.77 V
*/
		int colValues[]={150,150+47,150+47+47};
		int rowValues[]={47+47+150+330,47+47+150,47+47,47};
		TreeMap<Integer, Range> readouts=new TreeMap<>();
		for(int col=0;col<3;++col)
		{
			for(int row=0;row<4;++row)
			{
				int readout=(1024*rowValues[row])/(colValues[col]+rowValues[row]);
				Range r=new Range();
				r.col=col;
				r.row=row;
				r.readout=readout;
				r.index=indexes[row*3+col];
				r.ch=chars[row*3+col];
				readouts.put(readout, r);
			}
		}
		Range prev=new Range();
		for(Integer i:readouts.keySet())
		{
			Range r=readouts.get(i);
			int limit=prev.readout+(i-prev.readout)/2;
			r.minLimit=limit;
			prev.maxLimit=limit;
			System.out.println("limit: "+limit+" value: "+i+" -> "+readouts.get(i).ch+" diff: "+(i-prev.readout));
			prev=r;
		}
		for(Integer i:readouts.keySet())
		{
			Range r=readouts.get(i);
			System.out.println("if(value>="+r.minLimit+(r.maxLimit>-1?"&&value<"+r.maxLimit:"")+") pressedIndex="+r.index+"; // '"+r.ch+"' "+(5.0/1024.0*r.readout)+"V ("+(5.0/1024.0*r.minLimit)+"V-"+(5.0/1024.0*r.maxLimit)+"V)");
		}
	}
}

