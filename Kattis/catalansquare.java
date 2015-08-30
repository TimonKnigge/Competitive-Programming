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

public class catalansquare {
	public static void main(String[] args) {
		InputReader in = new InputReader(System.in);
		PrintWriter out = new PrintWriter(System.out);
		Solver s = new Solver();
		s.solve(in, out);
		out.close();
	}
	
	static class Solver {
		public void solve(InputReader in, PrintWriter out) {
			int n = in.nextInt();
			n += 1;
			int nn = n * 2;
			BigInteger TwoNOverN = BigInteger.ONE;
			for (int k = 1; k <= n; k += 1) {
				TwoNOverN = TwoNOverN
					.multiply(
						new BigInteger(
							Integer.toString(n + k)))
					.divide(new BigInteger(Integer.toString(k)));
			}
			out.println(TwoNOverN.divide(new BigInteger(Integer.toString(n + 1))).toString());
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
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}
			return tokenizer.nextToken();
		}
		public int nextInt() {
			return Integer.parseInt(next());
		}
	}
}
