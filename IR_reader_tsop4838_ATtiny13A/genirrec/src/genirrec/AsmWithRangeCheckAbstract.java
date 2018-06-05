package genirrec;

import java.util.ArrayList;
import java.util.List;

public class AsmWithRangeCheckAbstract extends AsmAbstract
{
	/**
	 * CPU frequency in Hz
	 */
	public int cpu_freq=0;
	/**
	 * Divisor of queried time base: TCNT0 overflow period is 256 and we query the Least significant byte
	 */
	private int divisor=256;

	class RangeCheckInsert
	{
		private List<Integer> ranges=new ArrayList<>();
		private List<String> labels=new ArrayList<>();
		private List<String> matchLabels=new ArrayList<>();
		private String rangeExitLabel;
		public RangeCheckInsert()
		{
			rangeExitLabel=createLabel("Range_EXIT");
		}
		public void generate(Object[] o)
		{
			int index=(Integer)o[0];
			if(ranges.size()>index)
			{
				int Tmicros=ranges.get(index);
				int freqTick=cpu_freq/divisor;
				int TtickMicros=1000000/freqTick;
				int n=Tmicros/TtickMicros;
				String lowByte="0x"+Integer.toHexString(n&0xFF);
				String highByte="0x"+Integer.toHexString(n>>8&0xFF);
				write("    ldi tmp2, ");
				writeObject(lowByte);
				write("\n    cp tmp0, tmp2\n    ldi tmp2, ");
				writeObject(highByte);
				write("\n    cpc tmp1, tmp2\n    brge ");
				writeObject(labels.get(index));
				write(" // If measured value is GT ");
				writeObject(Tmicros);
				write(" micros (");
				writeObject(n);
				write(" ticks)\n");
				writeObject(matchLabels.get(index));
				write(":\n");
			}
		}

		public int addRange(int tmicros) {
			ranges.add(tmicros);
			labels.add(createLabel("RangeGt_"+tmicros));
			int prevMicros=ranges.size()==1?0:ranges.get(ranges.size()-2);
			matchLabels.add(createLabel("Range_"+prevMicros+"_TO_"+tmicros));
			return ranges.size();
		}
	}
	private RangeCheckInsert currentRange;
	protected void rangeCheckEnd() {
		writeObject(currentRange.rangeExitLabel);
		write(":\n");
		currentRange=null;
	}

	protected void range(int Tmicros) {
		write("    rjmp ");
		writeObject(currentRange.rangeExitLabel);
		write("\n");
		int rangeindex=currentRange.addRange(Tmicros);
		writeObject(currentRange.labels.get(currentRange.labels.size()-1));
		write(":\n");
		deferred(currentRange::generate, rangeindex);
	}

	protected void rangeCheckStart() {
		if(currentRange!=null)
		{
			throw new RuntimeException("Rnage check block is not closed");
		}
		currentRange=new RangeCheckInsert();
		deferred(currentRange::generate, 0);
	}
	@Override
	protected void finish() {
		super.finish();
		if(currentRange!=null)
		{
			throw new RuntimeException("Rnage check block is not closed");
		}
	}
}
