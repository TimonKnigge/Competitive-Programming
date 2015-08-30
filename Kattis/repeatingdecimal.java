import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

import java.util.Arrays;
import java.math.BigInteger;

public class repeatingdecimal {
	public static void main(String[] args) {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);
		Solver s = new Solver();
		s.solve(in, out);
		out.close();
	}
	
	static class Solver {
		public void solve(InputReader in, PrintWriter out) {
			int a, b, c;
			while (true) {
				a = in.nextInt();
				b = in.nextInt();
				c = in.nextInt();
				if (c == -1) break;
				
				BigInteger A = new BigInteger(Integer.toString(a));
				BigInteger B = new BigInteger(Integer.toString(b));
				BigInteger res = A.multiply(BigInteger.TEN.pow(c)).divide(B);
				String ans = res.toString();

				out.print("0.");
				for (int i = 0; i < c - ans.length(); ++i)
					out.print('0');
				out.println(ans);
			}
		}
	}

	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		public InputReader(InputStream st) {
			reader = new BufferedReader(new InputStreamReader(st), 32768);
			tokenizer = null;
		}
		public String next() {
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					String s = reader.readLine();
					if (s == null) {
						tokenizer = null;
						break;
					}
					if (s.isEmpty()) continue;
					tokenizer = new StringTokenizer(s);
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return (tokenizer != null && tokenizer.hasMoreTokens()
				? tokenizer.nextToken() : null);
		}
		public int nextInt() {
			String s = next();
			if (s != null)
				return Integer.parseInt(s);
			else return -1; // handle appropriately
		}
	}
}
