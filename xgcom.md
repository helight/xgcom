# 1、Introduction #

A gui tools to help guys develop series port, like minicom. part code is form gtkterm-0.99.5.
# 2、Install： #
Source code：
http://code.google.com/p/xgcom/

svn checkout http://xgcom.googlecode.com/svn/trunk/ xgcom

get source code here , compile and install.

or you can get tar ball：

http://code.google.com/p/xgcom/downloads/list

Some lib and tools are needed：

make, automake，libglib2.0-dev，libvte-dev，libgtk2.0-dev

Run the command in xgcom folder ：

xgcom$ ./autogen.sh

xgcom$ make

xgcom$ sudo make install

xgcom$ xgcom

So have fun with it!!!

zlbgps has put this software into AUR pakeage library ，
so arch users can install this program with this command :yaourt -S xgcom

# 3、Some Features： #
1.send and receive data from com

2.configure the com (speed,data bit, stop bit, odd bit, contrl data)

3.sace and load the configure file (speed,data bit, stop bit, odd bit, data contrl)

4.show the data in HEX format

5.count the num of receive and send data (by byte)

6.log the receive data into file (append or cover)  The log file path:  getenv("HOME")/data\_uart\_time.txt

7.send file (choose and send file)

8.send data in HEX format

9.send data by interval， you can set the time by yourself

10.show ico in panel (you can show or hide the window by clicking it)

11.can type character in receive area, (just like minicom)

12.set the default configure file

13.local echo.

# 4、What will be in next version： #


# 5、Google groups about xgcom： #
Group name: xgcom

<table cellspacing='0'>
<blockquote><tr><td>
<img src='http://groups.google.com/intl/en/images/logos/groups_logo_sm.gif' />  </td></tr>
<tr><td>
<b>xgcom</b>
</td></tr>
<tr><td>
<a href='http://groups.google.com/group/xgcom'>Visit this group</a>
</td></tr>
</table></blockquote>

Group home page: https://groups.google.com/group/xgcom