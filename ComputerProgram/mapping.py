def map_to_donut(img_data, img_size_x, img_size_y, inner_circle_radius, outer_circle_radius):
    # Integrate over the radius between the inner and outer circle
    for r in range(inner_circle_radius, outer_circle_radius):
        # Integrate over the entire circumference at that radius
        for a in range(0,360):
            pass