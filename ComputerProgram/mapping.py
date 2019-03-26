import math
import numpy as np
from skimage.transform import rescale
def map_to_donut(img_data, img_size_x, img_size_y, inner_circle_fraction, outer_circle_fraction):

    inner_circle_radius = int((img_size_x/2) * inner_circle_fraction)
    outer_circle_radius = int((img_size_x/2) * outer_circle_fraction)
    circle_circumference = int(2*math.pi*outer_circle_radius)
   # print "Inner circle radius: %d, Outer circle radius %d" % (inner_circle_radius, outer_circle_radius)
   # print "Circle circumference: %d" % ( circle_circumference )
    mapped_img = []

    # Integrate over the radius between the inner and outer circle
    for r in np.linspace(inner_circle_radius, outer_circle_radius, outer_circle_radius- inner_circle_radius, endpoint = False):
        # Integrate over the entire circumference at that radius
        #print r
        row = []
        for a in np.linspace(360, 0, circle_circumference):
            pix_x = (int(math.cos(math.radians(a)) * r)) + img_size_x/2
            pix_y = (int(math.sin(math.radians(a)) * r)) + img_size_y/2
            row.append(img_data[(pix_x * img_size_x) + pix_y])
        print("\r%d of %d" %(r, img_size_x/2))
        mapped_img.extend(row)
            # X size, Y size, data
    return (circle_circumference, outer_circle_radius-inner_circle_radius, mapped_img)

def downscale( data):
    rescaled = rescale(data, 0.5)
    return rescaled