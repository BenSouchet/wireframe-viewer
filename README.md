# Fdf

Fdf is a program developed for my learning course at 42 school to view topological maps in a 3D space.
<img align="center" src="http://i.imgur.com/B9Ugscn.png" width="100%" />
Several options are available (see [Keyboard shortcuts](https://github.com/BenjaminSouchet/Fdf#keyboard-shortcuts) section for more infos) :
* Zoom and unzoom
* Move the map on the 3D space
* Rotate the map (on the three axes of rotation)
* Edit the display color of the maps
* Navigate between all preloader maps you launched

Infos : In the "maps" folder you will find examples maps with which you can launch the program.

## Install & launch
```bash
git clone https://github.com/BenjaminSouchet/Fdf ~/Fdf
cd ~/Fdf && ./fdf maps/good/mars.fdf
```
You have to launch the program with parameter(s). It's map(s) you would like to open at the execution of the program. Parameter(s) as to be the name(s) of valid filename(s).<br />

Some Examples :

Open only one map ⇣
```bash
./fdf maps/good/pyramide.fdf
```
Open several maps ⇣
```bash
./fdf maps/good/pyramide.fdf maps/good/mars.fdf
```
Open all maps of a folder ⇣
```bash
./fdf maps/good/*
```
## Keyboard shortcuts

<table width="100%">
<thead>
<tr>
<td width="100%" height="60px" align="center" cellpadding="0">
<strong>Description</strong>
</td>
<td width="100%" align="center" cellpadding="0">
<span style="width:50px">&nbsp;</span><strong>Key(s)</strong><span style="width:50px">&nbsp;</span>
</td>
</tr>
</thead>
<tbody>
<tr>
<td valign="top" height="30px">Close the program (aka quit/exit)</td>
<td valign="top" align="center"><kbd>&nbsp;esc&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Reset all the changes made for this map</td>
<td valign="top" align="center"><kbd>&nbsp;clear&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Change the display color of the current map (aka change color)</td>
<td valign="top" align="center"><kbd>&nbsp;shift&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Increase the global size of the map (aka zoom)</td>
<td valign="top" align="center"><kbd>&nbsp;+&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Decrease the global size of the map (aka unzoom)</td>
<td valign="top" align="center"><kbd>&nbsp;-&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Move the map to the up (aka move up)</td>
<td valign="top" align="center"><kbd>&nbsp;▲&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Move the map to the down (aka move down)</td>
<td valign="top" align="center"><kbd>&nbsp;▼&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Move the map to the left (aka width move left)</td>
<td valign="top" align="center"><kbd>&nbsp;◄&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Move the map to the right (aka move right)</td>
<td valign="top" align="center"><kbd>&nbsp;►&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Clockwise rotation on the X axe</td>
<td valign="top" align="center"><kbd>&nbsp;W&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Counter clockwise rotation on the X axe</td>
<td valign="top" align="center"><kbd>&nbsp;S&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Clockwise rotation on the Y axe</td>
<td valign="top" align="center"><kbd>&nbsp;D&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Counter clockwise rotation on the Y axe</td>
<td valign="top" align="center"><kbd>&nbsp;A&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Clockwise rotation on the Z axe</td>
<td valign="top" align="center"><kbd>&nbsp;E&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Counter clockwise rotation on the Z axe</td>
<td valign="top" align="center"><kbd>&nbsp;Q&nbsp;</kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Previous preloader map*</td>
<td valign="top" align="center"><kbd><center>&nbsp;page&nbsp;<br /> up</center></kbd></td>
</tr>
<tr>
<td valign="top" height="30px">Next preloader map*</td>
<td valign="top" align="center"><kbd>&nbsp;page&nbsp;<br /> down</kbd></td>
</tr>
</tbody>
</table>
*Only available if you lauched the program with more than one map.*

## Bad maps & errors

This program have a very complexe errors checker, so if you launch Fdf with bad maps you will see the type, the line and the column position of all errors of the bad map.

Example :

Let's try with maps of the "maps/bad" subfolder ⇣
```bash
./fdf maps/bad/*
```
You will show this in your shell ⇣
```bash
error: maps/bad/01.fdf (line 4 col 37)    --> Invalid Hexadecimal color code
error: maps/bad/02.fdf                    --> Lines aren't of the same length
error: maps/bad/03.fdf                    --> Lines aren't of the same length
error: maps/bad/04.fdf (line 5 col 18)    --> A sign must be followed only by digit(s)
error: maps/bad/05.fdf (line 5 col 36)    --> A sign must be followed only by digit(s)
error: maps/bad/06.fdf (line 4 col 38)    --> Invalid character
error: maps/bad/07.fdf (line 4 col 23)    --> A sign must be followed only by digit(s)
error: maps/bad/08.fdf (line 4 col 8)     --> Invalid character
error: maps/bad/09.fdf (line 3 col 38)    --> Invalid character
error: maps/bad/10.fdf                    --> No data in the input file
error: maps/bad/11.fdf                    --> No data in the input file
error: maps/bad/12.fdf                    --> No data in the input file
error: maps/bad/13.fdf (line 2 col 38)    --> Invalid Hexadecimal color code
error: maps/bad/14.fdf (line 2 col 38)    --> Invalid Hexadecimal color code
error: maps/bad/15.fdf (line 4 col 3)     --> Invalid character
```
## Contact & contribute
If you want to contact me, or fix/improve FdF, just send me a mail at **bsouchet@student.42.fr**
