import java.util.Locale;

public class localelist
{
    public static void main(String[] args) {
	Locale[] localeList = Locale.getAvailableLocales();

	for (int i = 0; i < localeList.length; i++ ) {
	    System.out.println(localeList[i].getDisplayCountry()
			       +"=" + localeList[i].getCountry()
			       +"=" + localeList[i].getDisplayLanguage()
			       +"=" + localeList[i].getLanguage());
	}
    }
}
