/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package org.jab.docsearch.gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Insets;
import java.awt.MediaTracker;
import java.awt.Toolkit;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JWindow;

import org.apache.log4j.Logger;
import org.jab.docsearch.DocSearch;
import org.jab.docsearch.utils.FileUtils;

/**
 * Class DocSplashViewer
 * 
 * @version $Id: DocSplashViewer.java,v 1.7 2005/10/11 21:04:38 henschel Exp $
 */
public class DocSplashViewer extends JPanel {
    /**
     * Logger
     */
    private Logger logger = Logger.getLogger(getClass().getName()); 
    private Image image = null;
    private String labelText = "Loading Please wait...";
    private JWindow j;
    private int imageHeight = 0;
    private int imageWwidth = 0;
    private String brokenImageString = "brokenImage.jpg";
    private MediaTracker tracker;
    private DocSearch monitor;
    private int sizeW = 900;
    private int sizeH = 940;
    private boolean isBroken = false;
    private String saveDir = "";
    private String lastStatus = "";
    private boolean hasMon = false;


    /**
     * Constructor of DocSplashViewer
     *
     * @param imageFileName  filename of image
     */
    public DocSplashViewer(String imageFileName) {
        image = loadImage(imageFileName);

        repaint();
    }


    /**
     * Constructor of DocSpashViewer
     *
     * @param imageFileName
     * @param labelText
     */
    public DocSplashViewer(String imageFileName, String labelText) {
        image = loadImage(imageFileName);
        this.labelText = labelText;

        repaint();
    }


    /**
     * Close splash screen
     */
    public void close() {
        if (j != null) {
            j.dispose();
        }
    }


    /**
     * Sets monitor
     *
     * @param mon
     */
    public void setMonitor(DocSearch mon) {
        hasMon = true;
        monitor = mon;

        repaint();

        StatusThread st = new StatusThread();
        st.start();
    }


    /**
     * Overwrite method from JComponent
     */
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.setColor(Color.blue);
        setBackground(Color.white);
        g.fillRect(0, 0, getWidth(), getHeight());

        g.setColor(Color.white);
        g.fillRect(0, 0, sizeW, sizeH);
        g.drawRect(0, 0, imageWwidth + 2, imageHeight + 2);

        if (! isBroken) {
            if ((imageWwidth != 0) && (imageHeight != 0)) {
                g.drawImage(image, 1, 1, imageWwidth, imageHeight, this);
            }

            g.fillRect(0, 0, imageWwidth, 17);
            g.setColor(Color.black);
            g.drawString(labelText, 10, 13);
        } else {
            if ((imageWwidth != 0) && (imageHeight != 0)) {
                g.drawImage(image, 0, 0, imageWwidth, imageHeight, this);
            } else {
                g.drawImage(image, 0, 0, this);
            }

            g.fillRect(0, 0, labelText.length() * 17, 20);
            g.drawString(labelText, 31, 41);
        }
    }


    /**
     * Load image
     *
     * @param imageFileName  image file name
     * @return               return loaded image or null
     */
    public Image loadImage(String imageFileName) {
        Image newImage = null;

        // image from URL
        if (imageFileName.toLowerCase().startsWith("http://")) {
            try {
                String fileOnly = imageFileName.substring((imageFileName.lastIndexOf("/") + 1), imageFileName.length());
                String domOnly = imageFileName.substring(0, (imageFileName.lastIndexOf("/") + 1));
                logger.debug("loadImage() file:" + fileOnly + " URL prefix:" + domOnly);
                convertURLToFile(imageFileName, fileOnly);
                if (! saveDir.equals("")) {
                    fileOnly = FileUtils.addFolder(saveDir, fileOnly);
                }

                newImage = Toolkit.getDefaultToolkit().getImage(fileOnly);
                tracker = new MediaTracker(this);
                tracker.addImage(newImage, 0);
                tracker.waitForAll();
                imageHeight = newImage.getHeight(this);
                imageWwidth = newImage.getWidth(this);
                if ((imageHeight <= 0) || (imageWwidth <= 0)) {
                    newImage = Toolkit.getDefaultToolkit().getImage(brokenImageString);
                    tracker = new MediaTracker(this);
                    tracker.addImage(newImage, 0);
                    tracker.waitForAll();
                    imageHeight = newImage.getHeight(this);
                    imageWwidth = newImage.getWidth(this);
                    logger.error("loadImage() BROKEN IMAGE - failed to load: " + fileOnly);
                    isBroken = true;
                } else {
                    isBroken = false;
                }

                if (! isBroken) {
                    logger.debug("loadImage() ...finished loading image from URL.");
                }
            } catch (InterruptedException ie) {
                logger.error("loadImage() FAILED TO LOAD IMAGE - Image problem", ie);
                isBroken = true;
            }
        // image from file
        } else {
            try {
                newImage = Toolkit.getDefaultToolkit().getImage(imageFileName);
                tracker = new MediaTracker(this);
                tracker.addImage(newImage, 0);
                tracker.waitForAll();
                imageHeight = newImage.getHeight(this);
                imageWwidth = newImage.getWidth(this);
                if ((imageHeight <= 0) || (imageWwidth <= 0)) {
                    newImage = Toolkit.getDefaultToolkit().getImage(brokenImageString);
                    logger.error("loadImage() BROKEN IMAGE - failed to load: " + imageFileName);
                    isBroken = true;
                    imageHeight = 30;
                    imageWwidth = 200;
                } else {
                    isBroken = false;
                }
            } catch (InterruptedException ie) {
                logger.error("loadImage() Image problem", ie);
            }
        }

        return newImage;
    }


    /**
     * Change image
     * 
     * @param imageFileName  image file name
     */
    public void changeImage(String imageFileName) {
        image = loadImage(imageFileName);

        repaint();
    }


    /**
     * return the screen size
     *
     * @return  screen height
     */
    public int getHeight() {
        return imageHeight;
    }


    /**
     * return the screen width
     *
     * @return  screen width
     */
    public int getWidth() {
        return imageWwidth;
    }


    /**
     * Diplay dialog
     */
    public void display() {
        j = new JWindow();
        j.getContentPane().setLayout(new GridLayout(1, 1));

        GridBagLayout gridbaglayout = new GridBagLayout();
        
        GridBagConstraints gridbagconstraints = new GridBagConstraints();
        j.getContentPane().setLayout(gridbaglayout);
        
        JScrollPane imageScroll = new JScrollPane(this);
        imageScroll.setPreferredSize(new Dimension(365, 365));
        
        gridbagconstraints.fill = GridBagConstraints.BOTH;
        gridbagconstraints.insets = new Insets(1, 1, 1, 1);
        gridbagconstraints.gridx = 0;
        gridbagconstraints.gridy = 0;
        gridbagconstraints.gridwidth = 1;
        gridbagconstraints.gridheight = 1;
        gridbagconstraints.weightx = 1.0D;
        gridbagconstraints.weighty = 1.0D;
        gridbaglayout.setConstraints(imageScroll, gridbagconstraints);
        j.getContentPane().add(imageScroll);

        Dimension screenD = Toolkit.getDefaultToolkit().getScreenSize();
        int screenWidth = screenD.width;
        int screenHeight = screenD.height;

        j.setLocation((screenWidth / 2) - (350 / 2), (screenHeight / 2) - (250 / 2));
        j.pack();
        j.setVisible(true);

        repaint();
    }


    /**
     * Method load image from URL and save as file local
     *
     * @param urlString     URL
     * @param fileToSaveAs  filename for saving
     */
    private void convertURLToFile(String urlString, String fileToSaveAs) {

        FileOutputStream outputStream = null;
        InputStream inputStream = null;
        try {
            URL url = new URL(urlString);
            File saveFile;
            if (saveDir.equals("")) {
                saveFile = new File(fileToSaveAs);                
            } else {
                saveFile = new File(saveDir, fileToSaveAs);
            }

            // don't overwrite existing file
            if (! saveFile.exists()) {
                logger.info("convertURLToFile() Refreshing image... " + saveFile);

                // open url
                outputStream = new FileOutputStream(saveFile);
                URLConnection conn = url.openConnection();
                conn.setDoInput(true);
                conn.setUseCaches(false);
                conn.connect();
                inputStream = conn.getInputStream();

                // read data and wrote to out
                int numBytes = 0;
                int curI;
                while ((curI = inputStream.read()) != -1) {
                    outputStream.write(curI);
                    numBytes++;
                }

                logger.debug("convertURLToFile() File " + fileToSaveAs + " has " + numBytes + " bytes.");
            } else {
                logger.info("convertURLToFile() Using cached image..." + saveFile);
            }
        } catch (IOException ioe) {
            logger.fatal("convertURLToFile() Error retrieving file " + urlString, ioe);
        } finally {
            if (inputStream != null) {
                try {
                    inputStream.close();
                } catch (IOException ioe) {
                    logger.error("convertURLToFile() can't close InputStream", ioe);
                }
            }
            if (outputStream != null) {
                try {
                    outputStream.close();
                } catch (IOException ioe) {
                    logger.error("convertURLToFile() can't close FileOutputStream", ioe);
                }
            }
        }
    }


    /**
     * Overwrite method from JComponent
     */
    public Dimension getPreferredSize() {
        int newW = 360;
        int newH = 360;

        if (image != null) {
            newW = image.getWidth(this);
            newH = image.getHeight(this);
        }

        return new Dimension(newW, newH);
    }


    /**
     * Class StatusThread
     */
    public class StatusThread implements Runnable {
        Thread statusValidator;

        /**
         * Method start
         */
        public void start() {
            if (statusValidator == null) {
                statusValidator = new Thread(this, "statusValidator");
                statusValidator.start();
            }
        }


        /**
         * Method stop
         */
        public void stop() {
            statusValidator.interrupt();
            statusValidator = null;
        }


        /**
         * Implementation of method run from interfaxe Runnable
         */
        public void run() {
            for (Thread thread = Thread.currentThread(); statusValidator == thread;) {
                try {
                    // we run validation in a thread so as not to interfere with repaints of GUI
                    if (hasMon) {
                        labelText = monitor.getCurStatus();
                        if (! lastStatus.equals(labelText)) {
                            lastStatus = labelText;
                            repaint();
                        }
                    }
                } catch (Exception e) {
                    logger.error("run() Loading thread was stopped!", e);
                } finally {
                    stop();
                    if (statusValidator != null) {
                        statusValidator.destroy();
                    }
                }
            }
        }
    }
}
