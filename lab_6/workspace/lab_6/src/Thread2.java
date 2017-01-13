public class Thread2 extends Thread {
	private char searchCharFrom;
	private Obraz image;
	private int numOfCharacters, threadNumber;
	private int[] counts;

	public Thread2(int thNum, char start, int numOfChars, Obraz img) {
		searchCharFrom = start;
		image = img;
		numOfCharacters = numOfChars;
		counts = new int[numOfCharacters];
		threadNumber = thNum;
	}

	@Override
	public void run() {
		for (int i = 0; i < numOfCharacters; ++i) {
			counts[i] = image
					.calculate_histogram_for_character((char) (searchCharFrom + i));
		}

		for (int j = 0; j < numOfCharacters; ++j) {
			String hist = "";
			for (int i = 0; i < counts[j] / 10; ++i)
				hist += "=";

			System.out.println("Thread " + threadNumber + ": "
					+ (char)(searchCharFrom + j) + " " + hist + " " + counts[j]);
		}

	}
}
