En el proyecto se busca desarrollar una aplicación que permita procesar los datos de un sensor incorporado en un sistema global de navegación por satélites (GNSS). Dicho procesamiento genera archivos en formato GPX para poder ser visualizado luego en GPS o por ejemplo google maps. Un ejemplo de dicha salida es la siguiente :
```xml
<?xml version="1.0" encoding="UTF-8"?>

<gpx version="1.1" creator="95.11 TP1 - Tracker" xmlns="http://www.topografix.com/GPX/1/1">
  <metadata>
	<name>Default</name>
	<time>2018-12-20T17:54:57.000Z</time>
  </metadata>
  <trk>
	<trkseg>
	  <trkpt lat="-34.617667" lon="-58.368450">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.617217" lon="-58.368517">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.617067" lon="-58.368733">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.617150" lon="-58.369350">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.617767" lon="-58.369483">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.618383" lon="-58.369233">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.618200" lon="-58.367283">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.616967" lon="-58.367433">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	  <trkpt lat="-34.617083" lon="-58.368733">
		<ele>0.000000</ele>
		<time>2018-09-30T17:54:57.000Z</time>
	  </trkpt>
	</trkseg>
  </trk>
</gpx>
```
Y este archivo se puede visualizar en un mapa de la siguiente forma :
![plot](https://user-images.githubusercontent.com/44123170/166584069-e083e7aa-8d30-4ff1-81ee-bd7d07d96464.png)

